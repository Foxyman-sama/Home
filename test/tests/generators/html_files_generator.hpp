#ifndef HTML_FILES_GENERATOR_HPP
#define HTML_FILES_GENERATOR_HPP

#include <format>
#include <limits>
#include <random>
#include <string>

#include "modules/core/hash_table.hpp"

struct GeneratedParams {
  std::string data;
  size_t number_of_files;
  size_t size_of_files;
};

class HTMLGenerator {
 private:
  GeneratedParams generated;

 public:
  void makeTextFileAndAppend(const std::string &filename, size_t size, const std::string &symbol) {
    ++generated.number_of_files;
    generated.size_of_files += size;
    appendBoundary();
    appendFilename(filename);
    generated.data.append(size, symbol[0]);
    generated.data.append(1, '\n');
  }

  void appendFile(const std::string &filename, const std::vector<char> &data) {
    ++generated.number_of_files;
    generated.size_of_files += data.size();
    appendBoundary();
    appendFilename(filename);
    for (auto &&ch : data) {
      generated.data.append(1, ch);
    }

    generated.data.append(1, '\n');
  }

  GeneratedParams getGeneratedParamsAndIfNotEmptyAddLastBounary() {
    if (generated.data.empty() == false) {
      appendBoundary();
    }

    return generated;
  }

  void clearGeneratedData() {
    generated.number_of_files = 0;
    generated.size_of_files = 0;
    generated.data.clear();
  }

 private:
  void appendBoundary() {
    generated.data.append(6, '-');
    generated.data.append("WebKitFormBoundary");
    generated.data.append(1, '\n');
  }
  void appendFilename(const std::string &filename) {
    generated.data.append("filename=\"");
    generated.data.append(filename);
    generated.data.append(1, '\"');
    generated.data.append("\r\n\r\n");
  }
};

static std::pair<GeneratedParams, HashTable<std::string, std::vector<char>>> fastGenerate(size_t number_of_files,
                                                                                          size_t max_size) {
  std::mt19937 seed { std::random_device {}() };
  std::uniform_int_distribution<size_t> sizes { 1, max_size };
  std::uniform_int_distribution<char> chars {
    std::numeric_limits<char>::min(),
    std::numeric_limits<char>::max(),
  };
  HTMLGenerator generator;
  HashTable<std::string, std::vector<char>> result;
  for (auto i { 0 }; i < number_of_files; ++i) {
    auto size { sizes(seed) };
    std::vector<char> data(size);
    for (auto &&el : data) {
      el = chars(seed);
    }

    auto filename { std::format("{}.bin", i) };
    result.emplace(filename, data);
    generator.appendFile(std::format("{}.bin", i), data);
  }

  return { generator.getGeneratedParamsAndIfNotEmptyAddLastBounary(), result };
}

#endif