// Hey Emacs, this is -*- coding: utf-8 -*-

/* eslint camelcase: [error, { allow: ['us_listen_socket'] }] */

// import { promisify } from 'node:util';

// For free TLS certificates at LetsEncrypt see e.g.:
// https://itnext.io/node-express-letsencrypt-generate-a-free-ssl-certificate-and-run-an-https-server-in-5-minutes-a730fbe528ca
// import https from 'https';
import http from 'node:http';

import express from 'express';

import { graphqlHTTP } from 'express-graphql';

import uWS from 'uWebSockets.js';

import { makeBehavior } from 'graphql-ws/lib/use/uWebSockets';

import { Container } from 'typedi';

import { ClusterClient, MqttClient, RedisClients } from '@s50/device-io';

import { buildSchema } from '~/lib/type-graphql/schema';

import { log } from '@s50/iso-share';

import { connectDevice, disconnectDevice } from '~/lib/device';
import type { DevicesRecord, DeviceRef } from '~/lib/device';

import { config } from '~/lib/config';

class App {
  constructor() {
    this._redisClients = new RedisClients({
      persistent: {
        socket: {
          host: config.persistentRedis.host,
          port: config.persistentRedis.port,
        },
      },
      volatile: {
        socket: {
          host: config.volatileRedis.host,
          port: config.volatileRedis.port,
        },
      },
    });

    this._mqttClient = new MqttClient(config.mqtt);

    this._clusterClient = new ClusterClient(
      this._mqttClient,
      this._redisClients,
    );

    Container.set('clutter-devices-record', this._clutterDevicesRecord);
    Container.set('local-device-ref', this._localDeviceRef);

    this._uwsGraphqlApp = uWS.App();
  }

  async initialise(): Promise<void> {
    await Promise.all([
      this._mqttClient.connect(),
      this._redisClients.connect(),
    ]);

    await this._clusterClient.connect();

    Container.set('redis-clients', this._redisClients);
    Container.set('mqtt-client', this._mqttClient);
    Container.set('cluster-client', this._clusterClient);

    // TODO: remove this 'redis-client' innject after refactoring
    //       type-graphql/resolvers/s50-config
    Container.set('redis-client', this._redisClients.persistent);

    await this.graphqlServersInitialise();

    await this.localDeviceUpdateInitialise();
  }

  private async graphqlServersInitialise(): Promise<void> {
    const schema = await buildSchema();

    const {
      protocol: httpProtocol,
      host: httpHost,
      port: httpPort,
      path: httpPath,
    } = config.graphql.http;

    const {
      protocol: wsProtocol,
      host: wsHost,
      port: wsPort,
      path: wsPath,
    } = config.graphql.ws;

    const httpUrl = `${httpProtocol}//${httpHost}:${httpPort}${httpPath}`;
    const wsUrl = `${wsProtocol}//${wsHost}:${wsPort}${wsPath}`;

    const app = express();

    app.use(
      httpPath,
      graphqlHTTP({
        schema,
        graphiql: true,
        // pretty: true,
        // TODO: as of express-graphql@0.12.0, subscriptions in graphiql do not
        //       work, check it at next versions.
        // graphiql: {
        //   subscriptionEndpoint: `${wsHref}`,
        // },
      }),
    );

    this._httpGraphqlServer = http.createServer(app);

    this._httpGraphqlServer.listen(httpPort, () => {
      log.info(`HTTP server ready at ${httpUrl}`);

      this._uwsGraphqlApp
        .ws(
          config.graphql.ws.path,
          makeBehavior(
            { schema },
            {
              open: (ws) => {
                this._uwsGraphqlAppSockets.add(ws);
              },
              close: (ws) => {
                this._uwsGraphqlAppSockets.delete(ws);
              },
            },
          ),
        )
        .listen(config.graphql.ws.port, (listenSocket) => {
          this._uwsGraphqlAppListenSocket = listenSocket;

          if (listenSocket) {
            log.info(`WebSockets server ready at ${wsUrl}`);
          } else {
            log.error(`Failed to start WebSockets server at ${wsUrl}`);
          }
        });
    });
  }

  private shutdownGraphqlServers(): void {
    if (this._uwsGraphqlAppListenSocket) {
      uWS.us_listen_socket_close(this._uwsGraphqlAppListenSocket);
      this._uwsGraphqlAppListenSocket = undefined;
    }

    [...this._uwsGraphqlAppSockets].forEach((ws) => {
      // see https://www.rfc-editor.org/rfc/rfc6455.html#section-7.1.5 for error codes
      ws.end(1001, 'WebSocket GraphQL server shutting-down');
    });

    this._httpGraphqlServer?.close();
  }

  async shutdown(): Promise<void> {
    try {
      if (this._updateDevicesInterval !== undefined) {
        clearInterval(this._updateDevicesInterval);
        this._updateDevicesInterval = undefined;
      }

      this.shutdownGraphqlServers();

      Container.remove([
        'redis-clients',
        'mqtt-client',
        'cluster-client',
        'clutter-devices-record',
      ]);

      const disconnectPromises = Object.values(this._clutterDevicesRecord).map(
        (device) => disconnectDevice(device),
      );

      await Promise.all(disconnectPromises);

      Object.keys(this._clutterDevicesRecord).forEach((key) => {
        delete this._clutterDevicesRecord[key];
      });

      await disconnectDevice(this._localDeviceRef.current);
      this._localDeviceRef.current = undefined;

      await this._clusterClient.disconnect();

      await Promise.all([
        this._redisClients.disconnect(),
        this._mqttClient.disconnect(),
      ]);
    } catch (cause) {
      log.report(cause);
      log.error('Error while graceful shutting-down. Crashing...');
      process.exit(1);
    }

    setTimeout(() => {
      log.error('Graceful shutting-down failed. Crashing...');
      process.exit(1);
    }, 60 * 1000).unref();
  }

  private readonly localDeviceUpdate = async (): Promise<void> => {
    const localDeviceDescriptor = await this._clusterClient.getLocalDevice();
    const deviceRef = this._localDeviceRef;

    if (localDeviceDescriptor?.id === deviceRef.current?.descriptor.id) {
      return;
    }

    if (deviceRef.current) {
      await disconnectDevice(deviceRef.current);
      deviceRef.current = undefined;
    }

    if (localDeviceDescriptor === undefined) {
      return;
    }

    deviceRef.current = await connectDevice(
      localDeviceDescriptor,
      this._redisClients,
      this._mqttClient,
    );
  };

  private async localDeviceUpdateInitialise(): Promise<void> {
    await this.localDeviceUpdate();

    this._updateDevicesInterval = setInterval(async () => {
      await this.localDeviceUpdate();
    }, 5 * 1000);
  }

  private readonly _redisClients;
  private readonly _mqttClient;
  private readonly _clusterClient;
  private _httpGraphqlServer?: http.Server;
  private _uwsGraphqlApp: uWS.TemplatedApp;
  private _uwsGraphqlAppListenSocket?: uWS.us_listen_socket;
  private _uwsGraphqlAppSockets = new Set<uWS.WebSocket>();
  private readonly _clutterDevicesRecord: DevicesRecord = {};
  private _localDeviceRef: DeviceRef = { current: undefined };
  private _updateDevicesInterval?: NodeJS.Timer;
}

export default async function main(): Promise<void> {
  const app = new App();
  await app.initialise();

  process.on('SIGINT', () => {
    log.info('Got SIGINT, gracefully shutting down');
    app.shutdown();
  });

  process.on('SIGTERM', () => {
    log.info('Got SIGTERM, gracefully shutting down');
    app.shutdown();
  });
}
