#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <modules/core/hash_table.hpp>

#include "html_maker.hpp"

template <typename Key, typename Value>
HashTable<Key, Value> generateFiles(size_t number_of_files, size_t max_size) {
  std::mt19937 seed { std::random_device {}() };
  std::uniform_int_distribution<size_t> sizes { 1, max_size };
  std::uniform_int_distribution<char> chars {
    std::numeric_limits<char>::min(),
    std::numeric_limits<char>::max(),
  };
  HashTable<Key, Value> result;
  for (auto i { 0 }; i < number_of_files; ++i) {
    auto size { sizes(seed) };
    Value data;
    data.resize(size);
    for (auto &&el : data) {
      el = chars(seed);
    }

    auto filename { std::format("{}.bin", i) };
    result.emplace(filename, data);
  }

  return result;
}
template <typename Key, typename Value>
std::pair<GeneratedParams, HashTable<Key, Value>> generateHTMLWithFiles(size_t number_of_files, size_t max_size) {
  auto files { generateFiles<Key, Value>(number_of_files, max_size) };
  HTMLMaker maker;
  for (auto &&[filename, filedata] : files) {
    maker.appendFile(filename, filedata);
  }

  return { maker.getGeneratedParamsAndIfNotEmptyAddLastBounary(), files };
}

#endif