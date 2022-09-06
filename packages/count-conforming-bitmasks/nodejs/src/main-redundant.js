// Hey Emacs, this is -*- coding: utf-8 -*-

/* eslint-disable no-bitwise */
/* eslint-disable no-plusplus */

/**
 * @param {number}  A
 * @param {number}  B
 * @param {number}  C
 * @returns {number}
 */
export const solution = (A, B, C) => {
  if (!(Number.isInteger(A) && A >= 0 && A <= 1_073_741_823)) {
    throw Error(`N = ${A} is outside valid range`);
  }

  if (!(Number.isInteger(B) && B >= 0 && B <= 1_073_741_823)) {
    throw Error(`N = ${B} is outside valid range`);
  }

  if (!(Number.isInteger(C) && C >= 0 && C <= 1_073_741_823)) {
    throw Error(`N = ${C} is outside valid range`);
  }

  const inputs = [A, B, C];

  const binaryWidth = 30;
  let mask = 1;

  const zeroLocations = [];

  for (let i = 0; i < binaryWidth; ++i) {
    if ((A & mask) === 0) {
      zeroLocations.push({
        position: i,
        value: 0,
      });
    }

    mask <<= 1;
  }

  return 0;
};
