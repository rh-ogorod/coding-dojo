// Hey Emacs, this is -*- coding: utf-8 -*-

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <random>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view.hpp>
#include <vector>

#include "cpp-utils/binary_form.hpp"
#include "main.hpp"

namespace views = ranges::views;

constexpr auto CYCLES_COUNT = 1'000'000;

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::random_device device;
  std::default_random_engine engine{device()};
  std::uniform_int_distribution<int32_t> distribution{1, 2'147'483'647};

  auto indices = views::iota(0) | views::take(CYCLES_COUNT);
  auto numsView = views::transform(indices, [&](auto /*i*/) {
    return distribution(engine);
  });

  int32_t binaryGap{0};
  double durationAvgNanoSecond{0};

  ranges::for_each(numsView, [&binaryGap, &durationAvgNanoSecond](int32_t num) {
    const auto start = std::chrono::high_resolution_clock::now();

    binaryGap = solution(num);

    const auto finish = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::nano> duration = finish - start;
    durationAvgNanoSecond += duration.count();
  });

  durationAvgNanoSecond /= CYCLES_COUNT;

  std::cout << "Binary gap solution() exec duration: " << std::setprecision(4)
            << durationAvgNanoSecond << " ns\n";

  // std::cout << "Binary gap random samples:\n";
  // ranges::for_each(numsView, [](int32_t num) {
  //   std::cout << BinaryForm{num} << " -> " << solution(num) << "\n";
  // });

  // std::cout << "Binary gap random samples:\n";
  // for (const auto num : nums) {
  //   std::cout << BinaryForm{num} << " -> " << solution(num) << "\n";
  // }

  return 0;
}
