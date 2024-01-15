#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

class Converter {
 public:
  static std::string vectorToString(const std::vector<char> &vec) noexcept {
    std::string result;
    std::ranges::copy(vec, std::back_inserter(result));
    return result;
  }

  static std::vector<char> stringToVector(const std::string &str) noexcept {
    std::vector<char> result;
    std::ranges::copy(str, std::back_inserter(result));
    return result;
  }
};

#endif