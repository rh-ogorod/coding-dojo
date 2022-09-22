// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __main_hpp__
#define __main_hpp__

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <range/v3/view.hpp>
#include <vector>

// #include <climits>
// #include <bitset>
// #include "cpp-utils/binary_form.hpp"

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
inline std::int32_t solution(std::int32_t N) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(N >= 0 && N <= 1'000'000'000);

  const int width = std::numeric_limits<std::uint32_t>::digits;

  const std::uint32_t n = N;
  std::uint32_t mask = 1;
  std::vector<std::uint32_t> constituents;

  for (int i = 0; i < width; ++i) {
    const auto constituent = n & mask;
    if (constituent != 0) {
      constituents.push_back(constituent);
    }
    mask <<= 1U;
  }

  std::cout << ranges::views::all(constituents);

  return N;
}

#endif // __main_hpp__
