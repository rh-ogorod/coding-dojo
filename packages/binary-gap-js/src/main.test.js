// Hey Emacs, this is -*- coding: utf-8 -*-
/* global describe it */

import assert from 'assert';

import { solution } from './main.js';

describe('Array', () => {
  describe('BinaryGap solution()', () => {
    it('should return 42', () => {
      assert.equal(solution(10), 42);
    });
  });
});
