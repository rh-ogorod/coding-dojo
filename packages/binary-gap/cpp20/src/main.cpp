// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#include <bitset>
#include <climits>
#include <iostream>

#include "cpp-utils/binary_form.hpp"

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << "Binary gap samples:\n"
            << BinaryForm{10} << " -> " << solution(10) << "\n"
            << BinaryForm{0b100'0000'0000'0000'0000'0000'0000'1010} << " -> "
            << solution(0b100'0000'0000'0000'0000'0000'0000'1010) << "\n";

  return 0;
}
