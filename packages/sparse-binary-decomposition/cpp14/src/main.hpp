// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __main_hpp__
#define __main_hpp__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

inline bool isSparse(std::uint32_t n) {
  const auto a = n + (n << 1);
  const auto b = a ^ (n << 1);

  if (n == b) {
    return true;
  }

  return false;
}

struct DecomposeResult {
  std::uint32_t left;
  std::uint32_t right;
  bool sparse;
};

inline DecomposeResult decompose(std::int32_t N) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(N >= 0 && N <= 1'000'000'000);

  DecomposeResult result{.sparse = false};

  constexpr int width = std::numeric_limits<std::uint32_t>::digits;

  std::uint32_t right = N;
  std::uint32_t left = 0;
  std::uint32_t mask = 1;
  int prv = 0;

  for (int i = 0; i < width; ++i) {
    const int cur = right & mask;

    if (cur != 0 && prv != 0) {
      right &= ~mask;
      left |= mask;
    }

    prv = right & mask;
    mask <<= 1;
  }

  result.left = left;
  result.right = right;

  if (isSparse(left) && isSparse(right)) {
    result.sparse = true;
  }

  return result;
}

inline std::int32_t solution(std::int32_t N) {
  const auto dec = decompose(N);

  if (dec.sparse) {
    return dec.right;
  }

  return -1;
}

#endif // __main_hpp__
