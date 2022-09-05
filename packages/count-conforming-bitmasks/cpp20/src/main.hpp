// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __count_conforming_bitmasks_hpp__
#define __count_conforming_bitmasks_hpp__

#include <cassert>
#include <cmath>
#include <cstdint>

inline auto solution(int32_t A, int32_t B, int32_t C) -> int32_t {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && A <= 1'073'741'823);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && B <= 1'073'741'823);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && C <= 1'073'741'823);
  constexpr int binaryWidth = 30;

  uint_fast32_t ua = A;
  uint_fast32_t ub = B;
  uint_fast32_t uc = C;

  uint_fast8_t az = 0;
  uint_fast8_t bz = 0;
  uint_fast8_t cz = 0;

  uint_fast8_t abz = 0;
  uint_fast8_t bcz = 0;
  uint_fast8_t acz = 0;

  uint_fast32_t mask = 1;

  for (int i = 0; i < binaryWidth; ++i) {
    if ((ua & mask) == 0) {
      az += 1;

      if ((ub & mask) == 0) {
        abz += 1;
      }

      if ((uc & mask) == 0) {
        acz += 1;
      }
    }

    if ((ub & mask) == 0) {
      bz += 1;

      if ((uc & mask) == 0) {
        bcz += 1;
      }
    }

    if ((uc & mask) == 0) {
      cz += 1;
    }

    mask <<= 1U;
  }

  uint_fast32_t powAz = (1U << az);
  uint_fast32_t powBz = (1U << bz);
  uint_fast32_t powCz = (1U << cz);

  uint_fast32_t powAbz = abz > 0 ? (1U << abz) : 0;
  uint_fast32_t powBcz = bcz > 0 ? (1U << bcz) : 0;
  uint_fast32_t powAcz = acz > 0 ? (1U << acz) : 0;

  return powAz + powBz + powCz - powAbz - powBcz - powAcz;
}

#endif // __count_conforming_bitmasks_hpp__
