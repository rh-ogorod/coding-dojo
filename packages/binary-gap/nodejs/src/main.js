// Hey Emacs, this is -*- coding: utf-8 -*-

/* eslint-disable no-bitwise */
/* eslint-disable no-plusplus */

/**
 * @param {number}  N
 * @returns {number}
 */
export const solution = (N) => {
  if (!(Number.isInteger(N) && N >= 1 && N <= 2_147_483_647)) {
    throw Error(`N = ${N} is outside valid range`);
  }

  const binaryWidth = 31;

  let binaryGap = 0;
  let currentGap = 0;
  let gapTrack = false;
  let mask = 1;

  for (let i = 0; i < binaryWidth; ++i) {
    if ((N & mask) !== 0) {
      if (gapTrack) {
        if (currentGap > binaryGap) {
          binaryGap = currentGap;
        }
        currentGap = 0;
      } else {
        gapTrack = true;
      }
    } else if (gapTrack) {
      ++currentGap;
    }

    mask <<= 1;
  }

  return binaryGap;
};
