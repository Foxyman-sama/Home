#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <ranges>

#include "html_maker.hpp"

template <typename Generated>
class Random {
 private:
  std::mt19937 seed;
  std::uniform_int_distribution<Generated> range;

 public:
  Random(Generated min, Generated max) : seed { std::random_device {}() }, range { min, max } {}

  Generated get() noexcept { return range(seed); }
};

template <typename Key, typename Value>
std::unordered_map<Key, Value> generateFiles(size_t number_of_files, size_t max_size) {
  Random<size_t> number_random { 1, max_size };
  Random<char> character_random {
    std::numeric_limits<char>::min(),
    std::numeric_limits<char>::max(),
  };
  std::unordered_map<Key, Value> result;
  for (auto i { 0 }; i < number_of_files; ++i) {
    Value data;
    data.resize(number_random.get());
    std::ranges::for_each(data, [&](auto &ch) { ch = character_random.get(); });
    result.emplace(std::format("{}.bin", i), data);
  }

  return result;
}
template <typename Key, typename Value>
std::pair<std::tuple<std::string, size_t, size_t>, std::unordered_map<Key, Value>> generateHTMLWithFiles(
    size_t number_of_files, size_t max_size) {
  auto files { generateFiles<Key, Value>(number_of_files, max_size) };
  HTMLMaker maker;
  std::ranges::for_each(files, [&](auto &&pair) { maker.appendFile(pair.first, pair.second); });
  return { maker.getFileGeneratedParamsAndIfNotEmptyAddLastBounary(), files };
}

#endif