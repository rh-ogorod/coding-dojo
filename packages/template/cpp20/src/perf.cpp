// Hey Emacs, this is -*- coding: utf-8 -*-

#include <array>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <random>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view.hpp>
#include <vector>

#include "binary_form.hpp"
#include "main.hpp"

namespace views = ranges::views;

constexpr auto CYCLES_COUNT = 1'000'000;

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::random_device device;
  std::default_random_engine engine{device()};
  std::uniform_int_distribution<int32_t> distribution{0, 1'073'741'823};

  auto indices = views::iota(0) | views::take(CYCLES_COUNT);
  auto inputsView = views::transform(indices, [&](auto /*i*/) {
    return std::array{
        distribution(engine), distribution(engine), distribution(engine)};
  });

  int32_t conformingIntsCount{0};
  double durationAvgNanoSecond{0};

  ranges::for_each(
      inputsView, [&conformingIntsCount, &durationAvgNanoSecond](auto input) {
        const auto start = std::chrono::high_resolution_clock::now();

        conformingIntsCount = solution(input[0], input[1], input[2]);

        const auto finish = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::nano> duration =
            finish - start;
        durationAvgNanoSecond += duration.count();
      });

  durationAvgNanoSecond /= CYCLES_COUNT;

  std::cout << "Count Conforming Bitmasks solution() exec duration: "
            << std::setprecision(4) << durationAvgNanoSecond << " ns\n";

  return 0;
}
