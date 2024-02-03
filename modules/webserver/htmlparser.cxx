#include "htmlparser.hpp"

namespace home::webserver {

HashTable<std::string, std::string> HTMLParser::parse(const std::string &str) {
  try {
    return tryParse(str);
  } catch (...) {
    throw;
  }
}
HashTable<std::string, std::string> HTMLParser::tryParse(const std::string &str) {
  selectBoundary(str);

  HashTable<std::string, std::string> result;
  for (; isEnd(str) == false; offset = findNextBoundary(str)) {
    result.emplace(parseFile(str));
  }

  return result;
}
void HTMLParser::selectBoundary(const std::string &str) {
  if (str.find(Delims::chrome_boundary) != std::string::npos) {
    current_delim = Delims::chrome_boundary;
  } else {
    current_delim = Delims::firefox_boundary;
  }
}
size_t HTMLParser::findNextBoundary(const std::string &str) { return str.find(current_delim, offset + 1); }
bool HTMLParser::isEnd(const std::string &str) {
  return str.find(current_delim, findNextBoundary(str)) == std::string::npos;
}

std::pair<std::string, std::string> HTMLParser::parseFile(const std::string &str) {
  return { parseFilename(str), parseData(str) };
}
std::string HTMLParser::parseFilename(const std::string &str) {
  auto [pos_beg, pos_end] { find(str, Delims::name_matcher_beg, Delims::name_matcher_end) };
  return extract(str, pos_beg, pos_end);
}
std::pair<size_t, size_t> HTMLParser::find(const std::string &str, const std::string_view &start,
                                           const std::string_view &end) {
  auto pos_beg { str.find(start, offset) + start.length() };
  auto pos_end { str.find(end, pos_beg) };
  return { pos_beg, pos_end };
}
std::string HTMLParser::extract(const std::string &str, size_t beg, size_t end) { return str.substr(beg, end - beg); }

std::string HTMLParser::parseData(const std::string &str) {
  auto [pos_beg, pos_end] { find(str, Delims::data_matcher_beg, current_delim) };
  auto pos_end_without_ending_character { pos_end - 1 };
  auto result { extract(str, pos_beg, pos_end_without_ending_character) };
  return result;
}

}  // namespace home::webserver