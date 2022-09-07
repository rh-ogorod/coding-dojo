// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#define BOOST_TEST_MODULE BinaryGap
#include <boost/test/unit_test.hpp>

// NOLINTNEXTLINE
BOOST_AUTO_TEST_CASE(binary_gap) {
  BOOST_REQUIRE_EQUAL(
      solution(
          0b11'1111'1111'1111'1111'1111'1001'1111,
          0b11'1111'1111'1111'1111'1111'0011'1111,
          0b11'1111'1111'1111'1111'1111'0110'1111),
      8);

  BOOST_REQUIRE_EQUAL(
      solution(
          0b11'1111'1111'1111'1111'1011'1001'1111,
          0b11'1111'1111'1111'1101'1001'0011'1111,
          0b11'1111'1111'1111'1111'1111'0110'1111),
      38);
}
