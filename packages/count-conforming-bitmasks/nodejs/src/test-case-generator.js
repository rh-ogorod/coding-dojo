// Hey Emacs, this is -*- coding: utf-8 -*-

/* eslint-disable no-bitwise */
/* eslint-disable no-plusplus */

class SuperSet {
  constructor() {
    /** @type {Array<Set<number>>} */
    this.sets = [new Set()];
  }

  /**
   * @param {number}  v
   * @returns {Set<number>}
   */
  add(v) {
    if (this.sets[this.sets.length - 1].size === 16777000) {
      this.sets.push(new Set());
    }

    return this.sets[this.sets.length - 1].add(v);
  }

  *[Symbol.iterator]() {
    for (const set of this.sets) {
      const vs = set.values();
      for (const v of vs) {
        yield v;
      }
    }
  }
}

/**
 * @param {number[]}  inputs
 * @returns {number[]}
 */
const solutionInputArray = (inputs) => {
  inputs.forEach((input) => {
    if (!(Number.isInteger(input) && input >= 0 && input <= 1_073_741_823)) {
      throw Error(`${input} is outside valid range`);
    }
  });

  const binaryWidth = 30;

  /** @type {Array<number[]>} */
  const zeroLocationsPerInput = [[], [], []];

  inputs.forEach((input, inputIndex) => {
    let mask = 1;

    for (let i = 0; i < binaryWidth; ++i) {
      if ((input & mask) === 0) {
        zeroLocationsPerInput[inputIndex].unshift(i);
      }
      mask <<= 1;
    }
  });

  /** @type {SuperSet} */
  const conformingInts = new SuperSet();

  zeroLocationsPerInput.forEach((zeroLocations, inputIndex) => {
    const extensionWidth = zeroLocations.length;
    const extensionsCount = 1 << extensionWidth;

    for (let n = 0; n < extensionsCount; ++n) {
      let conformingInt = inputs[inputIndex];

      for (let i = 0; i < extensionWidth; ++i) {
        const extensionBitLocation = zeroLocations[i];
        const extensionBitValue = (n & (1 << i)) !== 0 ? 1 : 0;
        if (extensionBitValue === 1) {
          conformingInt |= 1 << extensionBitLocation;
        }
      }

      try {
        conformingInts.add(conformingInt);
      } catch (e) {
        console.log(conformingInt.toString(2));
        throw e;
      }
    }
  });

  return [...conformingInts].sort();
};

/**
 * @param {number}  A
 * @param {number}  B
 * @param {number}  C
 * @returns {number[]}
 */
export const solution = (A, B, C) => {
  return solutionInputArray([A, B, C]);
};

const test0 = () => {
  const inputInts = /** @type {const} */ ([
    0b11_1111_1111_1111_1111_1111_1001_1111,
    0b11_1111_1111_1111_1111_1111_0011_1111,
    0b11_1111_1111_1111_1111_1111_0110_1111,
  ]);

  const conformingInts = solution(...inputInts);
  const conformingIntsCount = conformingInts.length;

  console.log(
    'inputs =',
    inputInts.map((inputInt) => inputInt.toString(2)),
  );

  console.log(
    'conforming ints =',
    conformingInts.map((conformingInt) => conformingInt.toString(2)),
  );

  console.log('conforming ints count =', conformingIntsCount);
  console.log();
};

const test1 = () => {
  const inputInts = /** @type {const} */ ([
    0b11_1111_1111_1111_1111_1011_1001_1111,
    0b11_1111_1111_1111_1101_1001_0011_1111,
    0b11_1111_1111_1111_1111_1111_0110_1111,
  ]);

  const conformingInts = solution(...inputInts);
  const conformingIntsCount = conformingInts.length;

  console.log(
    'inputs =',
    inputInts.map((inputInt) => inputInt.toString(2)),
  );

  console.log(
    'conforming ints =',
    conformingInts.map((conformingInt) => conformingInt.toString(2)),
  );

  console.log('conforming ints count =', conformingIntsCount);
  console.log();
};

const test2 = () => {
  const inputInts = /** @type {const} */ ([
    0b11_1111_0000_0000_0000_0000_0011_1111,
    0b11_1111_0000_0000_0000_0000_0011_1111,
    0b11_1111_0000_0000_0000_0000_0011_1111,
  ]);

  const conformingInts = solution(...inputInts);
  const conformingIntsCount = conformingInts.length;

  console.log(
    'inputs =',
    inputInts.map((inputInt) => inputInt.toString(2)),
  );

  // console.log(
  //   'conforming ints =',
  //   conformingInts.map((conformingInt) => conformingInt.toString(2)),
  // );

  console.log('conforming ints count =', conformingIntsCount);
  console.log();
};

const test3 = () => {
  const inputInts = /** @type {const} */ ([
    0b10_1010_1010_1010_1010_1010_1010_1010,
    0b01_0101_0101_0101_0101_0101_0101_0100,
    0b10_1010_1010_1010_1010_1010_1010_1010,
  ]);

  const conformingInts = solution(...inputInts);
  const conformingIntsCount = conformingInts.length;

  console.log(
    'inputs =',
    inputInts.map((inputInt) => inputInt.toString(2)),
  );

  // console.log(
  //   'conforming ints =',
  //   conformingInts.map((conformingInt) => conformingInt.toString(2)),
  // );

  console.log('conforming ints count =', conformingIntsCount);
  console.log();
};

const test4 = () => {
  const inputInts = /** @type {const} */ ([
    0b10_1010_1010_1010_1010_1010_1010_1010,
    0b01_0101_0101_0101_0101_0101_0101_1010,
    0b10_1010_1010_1010_1010_1010_1010_1010,
  ]);

  const conformingInts = solution(...inputInts);
  const conformingIntsCount = conformingInts.length;

  console.log(
    'inputs =',
    inputInts.map((inputInt) => inputInt.toString(2)),
  );

  // console.log(
  //   'conforming ints =',
  //   conformingInts.map((conformingInt) => conformingInt.toString(2)),
  // );

  console.log('conforming ints count =', conformingIntsCount);
  console.log();
};

test0();
test1();
test2();
test3();
test4();
