// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __main_hpp__
#define __main_hpp__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

inline bool isSparse(std::uint32_t n) {
  constexpr int width = std::numeric_limits<std::uint32_t>::digits;

  std::uint32_t mask = 1;
  std::uint32_t prevConstituent{};

  for (int i = 0; i < width; ++i) {
    const auto constituent = n & mask;

    if (i > 0 && constituent != 0 && prevConstituent != 0) {
      return false;
    }

    prevConstituent = constituent;

    mask <<= 1U;
  }

  return true;
}

struct DecomposeResult {
  bool areSparse;
  std::uint32_t left;
  std::uint32_t right;
};

inline DecomposeResult decompose(
    std::uint32_t n,
    const std::vector<std::uint32_t>& constituents,
    std::uint32_t selector) {
  DecomposeResult result{};

  std::uint32_t mask = 1;

  const int constituentsSize = constituents.size();

  for (int i = 0; i < constituentsSize; ++i) {
    const auto selectorBit = selector & mask;

    if (selectorBit != 0) {
      result.right += constituents[i];
      if (!isSparse(result.right)) {
        return {.areSparse = false};
      }
    }

    mask <<= 1U;
  }

  result.left = n - result.right;

  if (!isSparse(result.left)) {
    return {.areSparse = false};
  }

  result.areSparse = true;
  return result;
}

inline std::int32_t solution(std::int32_t N) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(N >= 0 && N <= 1'000'000'000);

  constexpr int width = std::numeric_limits<std::uint32_t>::digits;

  std::uint32_t n = N;
  std::uint32_t mask = 1;
  std::uint32_t prevMask{};
  std::uint32_t prevConstituent{};
  std::vector<std::uint32_t> constituents;

  for (int i = 0; i < width; ++i) {
    const auto constituent = n & mask;

    if (constituent != 0) {
      constituents.push_back(constituent);

      if (i > 0 && prevConstituent == 0) {
        constituents.push_back(prevMask);
      }
    }

    prevMask = mask;
    prevConstituent = constituent;

    mask <<= 1U;
  }

  const std::uint32_t maxSelector = (1U << constituents.size());

  for (std::uint32_t i = 0; i < maxSelector; ++i) {
    auto sums = decompose(n, constituents, i);

    if (sums.areSparse) {
      return sums.left;
    }
  }

  return -1;
}

#endif // __main_hpp__
