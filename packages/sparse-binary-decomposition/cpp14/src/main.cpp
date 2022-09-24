// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#include <bitset>
#include <iostream>
#include <range/v3/view.hpp>
#include <string>

#include "cpp-utils/binary_form.hpp"

namespace views = ranges::views;

// clang-format off

template <typename T>
std::string toBinariesList(const T& nums, std::string sep = ",") {
  return nums | views::transform([](auto num) {
    constexpr auto width = sizeof(decltype(num)) * CHAR_BIT;
    return std::bitset<width>{num}.to_string();
  }) | views::intersperse(sep) | views::join | ranges::to<std::string>();
}

// clang-format on

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << "solution(1) -> " << solution(1) << std::endl;

  std::cout << "solution(26) -> " << solution(26) << std::endl;

  std::cout << "solution(0) -> " << solution(0) << std::endl;

  return 0;
}
