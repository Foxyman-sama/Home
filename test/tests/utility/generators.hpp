#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <modules/core/hash_table.hpp>

#include "html_maker.hpp"

HashTable<std::string, std::vector<char>> generateFiles(size_t number_of_files, size_t max_size) {
  std::mt19937 seed { std::random_device {}() };
  std::uniform_int_distribution<size_t> sizes { 1, max_size };
  std::uniform_int_distribution<char> chars {
    std::numeric_limits<char>::min(),
    std::numeric_limits<char>::max(),
  };

  HashTable<std::string, std::vector<char>> result;
  for (auto i { 0 }; i < number_of_files; ++i) {
    auto size { sizes(seed) };
    std::vector<char> data(size);
    for (auto &&el : data) {
      el = chars(seed);
    }

    auto filename { std::format("{}.bin", i) };
    result.emplace(filename, data);
  }

  return result;
}
std::pair<GeneratedParams, HashTable<std::string, std::vector<char>>> generateHTMLWithFiles(size_t number_of_files,
                                                                                            size_t max_size) {
  auto files { generateFiles(number_of_files, max_size) };
  HTMLMaker maker;
  for (auto &&[filename, filedata] : files) {
    maker.appendFile(filename, filedata);
  }

  return { maker.getGeneratedParamsAndIfNotEmptyAddLastBounary(), files };
}

#endif