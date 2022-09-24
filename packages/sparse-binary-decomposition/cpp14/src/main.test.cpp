// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#define BOOST_TEST_MODULE BinaryGap
#include <boost/test/unit_test.hpp>

// NOLINTNEXTLINE
BOOST_AUTO_TEST_CASE(binary_gap) {
  BOOST_REQUIRE_EQUAL(18, solution(26));
  BOOST_REQUIRE_EQUAL(0, solution(0));
}
