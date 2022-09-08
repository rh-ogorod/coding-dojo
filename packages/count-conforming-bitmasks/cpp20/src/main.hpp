// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __count_conforming_bitmasks_hpp__
#define __count_conforming_bitmasks_hpp__

#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>

inline auto solution(int32_t A, int32_t B, int32_t C) -> int32_t {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && A <= 1'073'741'823);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && B <= 1'073'741'823);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && C <= 1'073'741'823);
  constexpr int binaryWidth = 30;

  const uint_fast32_t a = A;
  const uint_fast32_t b = B;
  const uint_fast32_t c = C;

  uint_fast8_t az = 0;
  uint_fast8_t bz = 0;
  uint_fast8_t cz = 0;

  uint_fast8_t abz = 0;
  uint_fast8_t bcz = 0;
  uint_fast8_t acz = 0;

  uint_fast8_t abcz = 0;

  uint_fast32_t mask = 1;

  for (int i = 0; i < binaryWidth; ++i) {
    if (((a & mask) == 0) && ((b & mask) == 0) && ((c & mask) == 0)) {
      abcz += 1;
    }

    if (((a & mask) == 0) && ((b & mask) == 0)) {
      abz += 1;
    }
    if (((b & mask) == 0) && ((c & mask) == 0)) {
      bcz += 1;
    }
    if (((a & mask) == 0) && ((c & mask) == 0)) {
      acz += 1;
    }

    if ((a & mask) == 0) {
      az += 1;
    }
    if ((b & mask) == 0) {
      bz += 1;
    }
    if ((c & mask) == 0) {
      cz += 1;
    }

    mask <<= 1U;
  }

  const uint_fast32_t powAz = 1U << az;
  const uint_fast32_t powBz = 1U << bz;
  const uint_fast32_t powCz = 1U << cz;

  const uint_fast32_t powAbz = 1U << abz;
  const uint_fast32_t powBcz = 1U << bcz;
  const uint_fast32_t powAcz = 1U << acz;

  const uint_fast32_t powAbcz = 1U << abcz;

  std::cout << "======== debugging metrics\n";

  std::cout << "az " << az << "\n";
  std::cout << "bz " << bz << "\n";
  std::cout << "cz " << cz << "\n";
  std::cout << "abz " << abz << "\n";
  std::cout << "bcz " << bcz << "\n";
  std::cout << "acz " << acz << "\n";
  std::cout << "abcz " << abcz << "\n";

  std::cout << "~~~~~~~~\n";

  std::cout << "powAz " << powAz << "\n";
  std::cout << "powBz " << powBz << "\n";
  std::cout << "powCz " << powCz << "\n";
  std::cout << "powAbz " << powAbz << "\n";
  std::cout << "powBcz " << powBcz << "\n";
  std::cout << "powAcz " << powAcz << "\n";
  std::cout << "powAbcz " << powAbcz << "\n";

  const uint_fast32_t abUnique = powAbz - powAbcz;
  const uint_fast32_t bcUnique = powBcz - powAbcz;
  const uint_fast32_t acUnique = powAcz - powAbcz;

  const uint_fast32_t aUnique = powAz - abUnique - acUnique - powAbcz;
  const uint_fast32_t bUnique = powBz - abUnique - bcUnique - powAbcz;
  const uint_fast32_t cUnique = powCz - bcUnique - acUnique - powAbcz;

  return aUnique + bUnique + cUnique + abUnique + bcUnique + acUnique + powAbcz;
}

#endif // __count_conforming_bitmasks_hpp__
