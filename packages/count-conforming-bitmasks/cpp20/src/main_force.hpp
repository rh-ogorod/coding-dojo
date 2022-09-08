// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __count_conforming_bitmasks_hpp__
#define __count_conforming_bitmasks_hpp__

#include <bitset>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

constexpr int binaryWidth = 30;
using Dragon = std::bitset<1U << static_cast<uint8_t>(binaryWidth)>;

inline auto createDragon(int32_t A, int32_t B, int32_t C)
    -> std::unique_ptr<Dragon> {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && A <= 1'073'741'823);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && B <= 1'073'741'823);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(A >= 0 && C <= 1'073'741'823);

  auto dragonUPtr = std::make_unique<Dragon>();

  dragonUPtr->set(0);

  return dragonUPtr;
}

#endif // __count_conforming_bitmasks_hpp__
