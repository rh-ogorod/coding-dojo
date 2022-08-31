// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __main_hpp__
#define __main_hpp__

#include <cassert>
#include <cstdint>
#include <limits>

inline auto solution(int N) -> int {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(N >= 1 && N <= 2'147'483'647);
  constexpr int binaryWidth = 31;

  int binaryGap = 0;
  int currentGap = 0;
  bool gapTrack = false;
  const uint_fast32_t un = N;
  uint_fast32_t mask = 1;

  for (int i = 0; i < binaryWidth; ++i) {
    if ((un & mask) != 0) {
      if (gapTrack) {
        if (currentGap > binaryGap) {
          binaryGap = currentGap;
        }
        currentGap = 0;
      }
      else {
        gapTrack = true;
      }
    }
    else if (gapTrack) {
      ++currentGap;
    }

    mask <<= 1U;
  }

  return binaryGap;
}

#endif // __main_hpp__
