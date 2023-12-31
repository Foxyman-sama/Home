#include "htmlparser.hpp"

namespace home::webserver {

HashTable<std::string, std::vector<char>> HTMLParser::parse(const std::string& str) {
  try {
    return tryParse(str);
  } catch (...) {
    throw;
  }
}
HashTable<std::string, std::vector<char>> HTMLParser::tryParse(const std::string& str) {
  HashTable<std::string, std::vector<char>> result;
  for (offset = str.find(delim); isLastBoundary(str) == false; offset = str.find(delim, offset + delim.size())) {
    result.emplace(parseFile(str));
  }

  return result;
}
bool HTMLParser::isLastBoundary(const std::string& src) { return src.find(delim, offset + 1) == std::string::npos; }
std::pair<std::string, std::vector<char>> HTMLParser::parseFile(const std::string& str) {
  auto filename { parseFilename(str) };
  auto data { parseData(str) };
  return { filename, data };
}
std::string HTMLParser::parseFilename(const std::string& str) {
  auto [pos_beg, pos_end] { find(str, name_matcher_beg, name_matcher_end) };
  return extract(str, pos_beg, pos_end);
}
std::pair<size_t, size_t> HTMLParser::find(const std::string& str, const std::string_view& start,
                                           const std::string_view& end) {
  auto pos_beg { str.find(start, offset) + start.length() };
  auto pos_end { str.find(end, pos_beg) };
  return { pos_beg, pos_end };
}
std::string HTMLParser::extract(const std::string& str, size_t beg, size_t end) { return str.substr(beg, end - beg); }

std::vector<char> HTMLParser::parseData(const std::string& str) {
  auto [pos_beg, pos_end] { find(str, data_matcher_beg, delim) };
  auto pos_end_without_ending_character { pos_end - 1 };
  auto data { extract(str, pos_beg, pos_end_without_ending_character) };
  return stringToVector(data);
}
std::vector<char> HTMLParser::stringToVector(const std::string& str) {
  std::vector<char> result;
  result.reserve(str.length());
  for (auto&& ch : str) {
    result.emplace_back(ch);
  }

  return result;
}

}  // namespace home::webserver