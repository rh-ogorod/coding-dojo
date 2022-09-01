// Hey Emacs, this is -*- coding: utf-8 -*-

import { solution } from './main.js';

/**
 * @returns {Promise<void>}
 */
(async () => {
  console.log('Binary gap samples:');
  console.log(Number(10).toString(2), '->', solution(10));
  console.log(
    Number(0b100_0000_0000_0000_0000_0000_0000_1010).toString(2),
    '->',
    solution(0b100_0000_0000_0000_0000_0000_0000_1010),
  );
})();
