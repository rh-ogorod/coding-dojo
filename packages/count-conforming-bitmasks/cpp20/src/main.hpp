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

  const int_fast32_t a = A;
  const int_fast32_t b = B;
  const int_fast32_t c = C;

  int az = 0;
  int bz = 0;
  int cz = 0;

  int abz = 0;
  int bcz = 0;
  int acz = 0;

  int abcz = 0;

  int_fast32_t mask = 1;

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

    mask <<= 1;
  }

  const int_fast32_t powAz = (1 << az);
  const int_fast32_t powBz = (1 << bz);
  const int_fast32_t powCz = (1 << cz);

  const int_fast32_t powAbz = (1 << abz);
  const int_fast32_t powBcz = (1 << bcz);
  const int_fast32_t powAcz = (1 << acz);

  const int_fast32_t powAbcz = (1 << abcz);

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

  const int_fast32_t abUnique = powAbz - powAbcz;
  const int_fast32_t bcUnique = powBcz - powAbcz;
  const int_fast32_t acUnique = powAcz - powAbcz;

  const int_fast32_t aUnique = powAz - abUnique - acUnique - powAbcz;
  const int_fast32_t bUnique = powBz - abUnique - bcUnique - powAbcz;
  const int_fast32_t cUnique = powCz - bcUnique - acUnique - powAbcz;

  return aUnique + bUnique + cUnique + abUnique + bcUnique + acUnique + powAbcz;
}

#endif // __count_conforming_bitmasks_hpp__
