// Hey Emacs, this is -*- coding: utf-8 -*-
#ifndef __force_hpp__
#define __force_hpp__

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
// #include <range/v3/algorithm/reverse.hpp>
#include <vector>

constexpr int binaryWidth = 30;
using Dragon = std::bitset<1U << static_cast<uint8_t>(binaryWidth)>;

template <std::size_t ARITY>
inline auto createDragon(std::array<std::uint32_t, ARITY> params)
    -> std::unique_ptr<Dragon> {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(!params.empty());

  for (auto param : params) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    assert(param >= 0 && param <= 1'073'741'823);
  }

  std::array<std::vector<uint8_t>, ARITY> zeroLocationsPerParam;

  for (auto paramIndex = 0; auto param : params) {
    uint_fast32_t mask = 1;

    for (auto i = 0; i < binaryWidth; ++i) {
      if ((param & mask) == 0) {
        zeroLocationsPerParam.at(paramIndex).push_back(i);
      }
      mask <<= 1U;
    }

    auto& zeroLocations = zeroLocationsPerParam.at(paramIndex);
    std::reverse(zeroLocations.begin(), zeroLocations.end());

    // ranges::reverse(zeroLocationsPerParam.at(paramIndex));

    // std::cout << ranges::views::transform(
    //                  zeroLocationsPerParam[paramIndex],
    //                  [](auto loc) {
    //                    return +loc;
    //                  })
    //           << "\n";

    ++paramIndex;
  }

  auto dragonUPtr = std::make_unique<Dragon>();

  for (auto paramIndex = 0;
       std::vector<uint8_t> & zeroLocations : zeroLocationsPerParam) {
    auto extensionWidth = zeroLocations.size();
    auto extensionsCount = 1U << extensionWidth;

    for (std::size_t n = 0; n < extensionsCount; ++n) {
      auto conformingInt = params.at(paramIndex);

      for (std::size_t i = 0; i < extensionWidth; ++i) {
        const auto extensionBitLocation = zeroLocations[i];
        const auto extensionBitValue = (n & (1U << i)) != 0 ? 1 : 0;
        if (extensionBitValue == 1) {
          conformingInt |= 1U << extensionBitLocation;
        }
      }

      dragonUPtr->set(conformingInt);
    }

    ++paramIndex;
  }

  return dragonUPtr;
}

inline auto solution(std::uint32_t A, std::uint32_t B, std::uint32_t C)
    -> std::uint32_t {
  const auto dragonUPtr = createDragon(std::array{
      static_cast<std::uint32_t>(A),
      static_cast<std::uint32_t>(B),
      static_cast<std::uint32_t>(C)});

  return dragonUPtr->count();
}

#endif // __force_hpp__
