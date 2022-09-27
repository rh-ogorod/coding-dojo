// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#include <bitset>
#include <iostream>
#include <string>

#include "cpp-utils/binary_form.hpp"

std::string bin(const DecomposeResult& decomposeResult) {
  constexpr int width = std::numeric_limits<std::uint32_t>::digits;

  return "[" + std::bitset<width>{decomposeResult.left}.to_string() + "," +
         std::bitset<width>{decomposeResult.right}.to_string() + "]";
}

std::string dec(const DecomposeResult& decomposeResult) {
  return "[" + std::to_string(decomposeResult.left) + "," +
         std::to_string(decomposeResult.right) + "]";
}

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  auto sol = decompose(0);
  std::cout << "decompose(0) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(1);
  std::cout << "decompose(1) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(2);
  std::cout << "decompose(2) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(3);
  std::cout << "decompose(3) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(7);
  std::cout << "decompose(7) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(110);
  std::cout << "decompose(110) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(26);
  std::cout << "decompose(26) -> " << dec(sol) << " " << bin(sol) << std::endl;

  sol = decompose(999999999);
  std::cout << "decompose(999999999) -> " << dec(sol) << " " << bin(sol)
            << std::endl;

  // std::cout << "decompose(1000000000) -> " << decompose(1000000000) <<
  // std::endl;

  return 0;
}
