// Hey Emacs, this is -*- coding: utf-8 -*-

#include "main.hpp"

#define BOOST_TEST_MODULE BinaryGap
#include <boost/test/unit_test.hpp>

// NOLINTNEXTLINE
BOOST_AUTO_TEST_CASE(binary_gap) {
  BOOST_ASSERT(
      std::set<std::uint32_t>({5, 8, 9, 10, 16, 17, 18, 21}) ==
      getSparseDecompositionParts(26));

  BOOST_ASSERT(
      std::set<std::uint32_t>({36, 37, 41, 42, 68, 69, 73, 74}) ==
      getSparseDecompositionParts(110));

  BOOST_ASSERT(std::set<std::uint32_t>() == getSparseDecompositionParts(0));
}
