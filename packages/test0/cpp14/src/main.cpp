// Hey Emacs, this is -*- coding: utf-8 -*-
// clang-format off

// #include "main.hpp"

// #include <algorithm>
// #include <boost/algorithm/string.hpp>
#include <iostream>
// #include <range/v3/view.hpp>
#include <string>

// #include "cpp-utils/binary_form.hpp"

// namespace views = ranges::views;

template<typename T>
std::string toBinariesList(const T& nums) {
  // return nums | views::transform([](auto num) {
  //   return std::to_string(num);
  // }) | views::intersperse(",") | views::join | ranges::to<std::string>();

  // return nums | views::transform([](auto num) {
  //   return std::to_string(num);
  // }) | views::intersperse("A") | views::join | ranges::to<std::string>();

  // std::vector<std::string> numStrs;

  // std::transform(
  //   nums.begin(), nums.end(),
  //   numStrs.begin(),
  //   [](auto num) {
  //     return std::to_string(num);
  //   }
  // );

  // return boost::algorithm::join(numStrs, ",");

  return std::to_string(nums[0]);
}

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  // auto sparseDecompositionParts = getSparseDecompositionParts(110);

  // std::cout << "getSparseDecompositionParts(110) -> "
  //           << views::all(sparseDecompositionParts) << ":" << std::endl;

  // std::vector<int> v{{1,2,3,4}};
  std::cout << std::to_string(10) << "\n";

  // sparseDecompositionParts = getSparseDecompositionParts(26);

  // std::cout << "getSparseDecompositionParts(26) -> "
  //           << views::all(sparseDecompositionParts) << std::endl;

  // std::cout << "solution(26) -> " << solution(26) << std::endl;

  return 0;
}
