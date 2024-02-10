#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <ranges>

#include "html_maker.hpp"

namespace home::test_utility {

template <typename Returned>
[[nodiscard]] Returned randomize(const Returned start, const Returned end) noexcept {
  std::mt19937 seed { std::random_device {}() };
  std::uniform_int_distribution<Returned> range { start, end };
  return range(seed);
}

}  // namespace home::test_utility

std::unordered_map<std::string, std::string> generateFiles() {
  using home::test_utility::randomize;

  constexpr auto char_min { std::numeric_limits<char>::min() };
  constexpr auto char_max { std::numeric_limits<char>::max() };
  constexpr auto size_min { 1 };
  constexpr auto size_max { 1'000 };
  const auto number_of_files { randomize(1, 1'000) };
  std::unordered_map<std::string, std::string> result;
  for (auto i { 0 }; i < number_of_files; ++i) {
    std::string data(randomize(size_min, size_max), '\0');
    for_each(data, [&](auto &ch) { ch = randomize(char_min, char_max); });
    result.emplace(std::format("{}.bin", i), data);
  }

  return result;
}

#endif