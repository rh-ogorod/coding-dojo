// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __main_hpp__
#define __main_hpp__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <range/v3/view.hpp>
#include <set>
#include <vector>

// #include <climits>
// #include <bitset>
// #include "cpp-utils/binary_form.hpp"

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
inline bool isSparse(std::uint32_t n) {
  constexpr int width = std::numeric_limits<std::uint32_t>::digits;

  std::uint32_t mask = 1;

  for (int i = 0; i < width; ++i) {
    const auto constituent = n & mask;

    if (constituent != 0) {
      if (i > 0) {
        const auto prevMask = mask >> 1U;
        const auto prevConstituent = n & prevMask;

        if (prevConstituent != 0) {
          return false;
        }
      }
    }

    mask <<= 1U;
  }

  return true;
}

struct SplitResult {
  std::uint32_t left;
  std::uint32_t right;
};

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
inline SplitResult split(
    std::uint32_t n,
    const std::vector<std::uint32_t>& constituents,
    std::uint32_t selector) {
  SplitResult result{};

  std::uint32_t mask = 1;

  const auto constituentsSize = constituents.size();

  for (int i = 0; i < constituentsSize; ++i) {
    const auto selectorBit = selector & mask;

    if (selectorBit != 0) {
      result.right += constituents[i];
    }

    mask <<= 1U;
  }

  result.left = n - result.right;

  return result;
}

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
inline std::int32_t solution(std::int32_t N) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(N >= 0 && N <= 1'000'000'000);

  constexpr int width = std::numeric_limits<std::uint32_t>::digits;

  const std::uint32_t n = N;
  std::uint32_t mask = 1;
  std::vector<std::uint32_t> constituents;

  for (int i = 0; i < width; ++i) {
    const auto constituent = n & mask;

    if (constituent != 0) {
      constituents.push_back(constituent);

      if (i > 0) {
        const auto prevMask = mask >> 1U;
        const auto prevConstituent = n & prevMask;

        if (prevConstituent == 0) {
          constituents.push_back(prevMask);
        }
      }
    }

    mask <<= 1U;
  }

  if (constituents.size() < 2) {
    return -1;
  }

  const std::uint32_t maxSelector = (1U << constituents.size()) - 1;
  std::set<std::uint32_t> sparseParts;

  for (int i = 1; i < maxSelector; ++i) {
    auto sums = split(n, constituents, i);

    if (isSparse(sums.right) && isSparse(sums.left)) {
      sparseParts.insert(sums.right);
      sparseParts.insert(sums.left);
    }
  }

  std::cout << ranges::views::all(constituents) << std::endl;
  std::cout << ranges::views::all(sparseParts) << std::endl;

  return N;
}

#endif // __main_hpp__
