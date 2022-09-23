// Hey Emacs, this is -*- coding: utf-8 -*-

/* eslint-disable no-bitwise */
/* eslint-disable no-plusplus */

/**
 * @param {number}  N
 * @returns {number}
 */
export const solution = (N) => {
  if (!Number.isInteger(N)) {
    throw Error(`N = ${N} should be integer`);
  }

  return N;
};
