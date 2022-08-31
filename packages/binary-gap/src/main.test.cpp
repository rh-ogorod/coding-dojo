// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#define BOOST_TEST_MODULE SolutionTest
#include <boost/test/unit_test.hpp>

// NOLINTNEXTLINE
BOOST_AUTO_TEST_CASE(solution_test) {
  BOOST_REQUIRE_EQUAL(solution(9), 2); // 1001
  BOOST_REQUIRE_EQUAL(solution(529), 4); // 1000010001
  BOOST_REQUIRE_EQUAL(solution(20), 1); // 10100
  BOOST_REQUIRE_EQUAL(solution(15), 0); // 1111
  BOOST_REQUIRE_EQUAL(solution(32), 0); // 100000
}

// #include <cassert>
// #include <concepts/concepts.hpp>
// #include <iostream>

// auto main(int /*argc*/, char* /*argv*/[]) -> int {
//   // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
//   assert(warp() == 42);

//   std::cout << "Tests passed!" << std::endl;

//   return 0;
// }
