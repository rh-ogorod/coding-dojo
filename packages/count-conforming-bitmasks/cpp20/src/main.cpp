// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#include <bitset>
#include <climits>
#include <cstdint>
#include <iostream>

#include "cpp-utils/binary_form.hpp"

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  constexpr std::int32_t A = 0b11'1111'1111'1111'1111'1111'1001'1111;
  constexpr std::int32_t B = 0b11'1111'1111'1111'1111'1111'0011'1111;
  constexpr std::int32_t C = 0b11'1111'1111'1111'1111'1111'0110'1111;

  const auto result = solution(A, B, C);
  // const auto result = 1;

  std::cout << "Count Conforming Bitmasks Example:\n"
            << "A = " << BinaryForm{A} << "\n"
            << "B = " << BinaryForm{B} << "\n"
            << "C = " << BinaryForm{C} << "\n"
            << "solution(A, B, C) == " << result << std::endl;

  return 0;
}
