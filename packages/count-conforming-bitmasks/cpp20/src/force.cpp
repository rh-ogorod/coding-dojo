// Hey Emacs, this is -*- coding: utf-8 -*-

#include "force.hpp"

#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

#include "cpp-utils/binary_form.hpp"

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  uint32_t A;
  uint32_t B;
  uint32_t C;
  std::unique_ptr<Dragon> dragonUPtr;

  A = 0b11'1111'1111'1111'1111'1111'1001'1111U;
  B = 0b11'1111'1111'1111'1111'1111'0011'1111U;
  C = 0b11'1111'1111'1111'1111'1111'0110'1111U;
  dragonUPtr = createDragon(std::array{A, B, C});

  std::cout << "Count Conforming Bitmasks Example:\n"
            << "A = " << BinaryForm{A} << "\n"
            << "B = " << BinaryForm{B} << "\n"
            << "C = " << BinaryForm{C} << "\n"
            << "solution(A, B, C) == " << dragonUPtr->count() << "\n"
            << std::endl;

  A = 0b10'1010'1010'1010'1010'1010'1010'1010;
  B = 0b01'0101'0101'0101'1010'1010'1010'1010;
  C = 0b10'1010'1010'1010'1010'1010'1010'1010;
  dragonUPtr = createDragon(std::array{A, B, C});

  std::cout << "Count Conforming Bitmasks Example:\n"
            << "A = " << BinaryForm{A} << "\n"
            << "B = " << BinaryForm{B} << "\n"
            << "C = " << BinaryForm{C} << "\n"
            << "solution(A, B, C) == " << dragonUPtr->count() << "\n"
            << std::endl;

  A = 0b11'1111'0000'0000'0000'0000'0000'0000;
  B = 0b11'1111'0000'0000'0000'0000'0000'0000;
  C = 0b11'1111'0000'0000'0000'0000'0000'0000;
  dragonUPtr = createDragon(std::array{A, B, C});

  std::cout << "Count Conforming Bitmasks Example:\n"
            << "A = " << BinaryForm{A} << "\n"
            << "B = " << BinaryForm{B} << "\n"
            << "C = " << BinaryForm{C} << "\n"
            << "solution(A, B, C) == " << dragonUPtr->count() << std::endl;

  return 0;
}
