// Hey Emacs, this is -*- coding: utf-8 -*-

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <random>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view.hpp>
#include <ratio>
#include <vector>

#include "cpp-utils/binary_form.hpp"
#include "main.hpp"

namespace views = ranges::views;

// constexpr auto CYCLES_COUNT = 1'000'000;
// constexpr auto CYCLES_COUNT = 1'000;
// constexpr auto CYCLES_COUNT = 10;
constexpr auto CYCLES_COUNT = 100;

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::random_device device;
  std::default_random_engine engine{device()};
  std::uniform_int_distribution<int32_t> distribution{0, 1'000'000'000};

  auto indices = views::iota(0) | views::take(CYCLES_COUNT);
  auto numsView = views::transform(indices, [&](auto /*i*/) {
    return distribution(engine);
  });

  int32_t result{0};
  double durationAvgNanoSecond{0};

  ranges::for_each(numsView, [&result, &durationAvgNanoSecond](int32_t num) {
    const auto start = std::chrono::high_resolution_clock::now();

    // result = solution(num);
    result = solution(999999999);

    const auto finish = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> duration = finish - start;
    durationAvgNanoSecond += duration.count();
  });

  durationAvgNanoSecond /= CYCLES_COUNT;

  std::cout << "solution() exec duration: " << std::setprecision(4)
            << durationAvgNanoSecond << " ms\n";

  std::cout << "Should be no longer than 100 ms by codility test\n";

  return 0;
}
