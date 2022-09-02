// Hey Emacs, this is -*- coding: utf-8 -*-
/* global describe it */

import assert from 'assert';

import { solution } from './main.js';

describe('BinaryGap solution()', () => {
  it('should return 2', () => {
    assert.equal(solution(9), 2);
  });

  it('should return 4', () => {
    assert.equal(solution(529), 4);
  });

  it('should return 1', () => {
    assert.equal(solution(20), 1);
  });

  it('should return 0', () => {
    assert.equal(solution(15), 0);
  });

  it('should return 0', () => {
    assert.equal(solution(32), 0);
  });
});
