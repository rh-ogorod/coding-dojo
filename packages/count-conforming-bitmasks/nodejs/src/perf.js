// Hey Emacs, this is -*- coding: utf-8 -*-

import { solution } from './main.js';

const CYCLES_COUNT = 1_000_000;

/**
 * @returns {Promise<void>}
 */
(async () => {
  const nums = Array.from({ length: CYCLES_COUNT }, (_v, _i) => {
    return Math.ceil(Math.random() * 2_147_483_647);
  });

  let binaryGap;
  let durationAvg = 0;

  nums.forEach((N) => {
    const start = performance.now();

    binaryGap = solution(N);

    const finish = performance.now();
    const duration = finish - start;
    durationAvg += duration;
  });

  durationAvg /= CYCLES_COUNT;

  console.log(
    `Binary gap solution() exec duration: ${durationAvg * 10 ** 6} ns`,
  );
})();
