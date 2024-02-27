#include "html_parser.hpp"

namespace home::webserver {

// Extractor

Extractor::Extractor(const std::string &str, const std::string_view &boundary)
    : str { str }, boundary { boundary }, offset { str.find(boundary) } {}

std::string Extractor::extract(const std::string_view &beg, const std::string_view &end, size_t right_offset) {
  auto [pos_beg, pos_end] { find(beg, end) };
  auto length { pos_end - pos_beg - right_offset };
  return str.substr(pos_beg, length);
}
std::pair<size_t, size_t> Extractor::find(const std::string_view &beg, const std::string_view &end) {
  auto pos_beg { str.find(beg, offset) + beg.length() };
  auto pos_end { str.find(end, pos_beg) };
  return { pos_beg, pos_end };
}
size_t Extractor::getFileNextOffset() const noexcept { return str.find(boundary, offset + 1); }

void Extractor::moveOffset() { offset = getFileNextOffset(); }

bool Extractor::isLastBoundary() const noexcept { return getFileNextOffset() != std::string::npos; }

// HTMLParser

std::unordered_map<std::string, std::string> HTMLParser::parse(const std::string &str) {
  try {
    return tryParse(str);
  } catch (std::exception &e) {
    throw e;
  }
}
std::unordered_map<std::string, std::string> HTMLParser::tryParse(const std::string &str) {
  selectBoundary(str);
  return parseFiles(str);
}
void HTMLParser::selectBoundary(const std::string &str) {
  if (isBoundaryFound(str, Boundary::chrome)) {
    current_delim = Boundary::chrome;
  } else if (isBoundaryFound(str, Boundary::firefox)) {
    current_delim = Boundary::firefox;
  } else {
    throw std::runtime_error { "Unknown target." };
  }
}
const bool HTMLParser::isBoundaryFound(const std::string &str, const std::string_view &boundary) const noexcept {
  return str.find(boundary) != std::string::npos;
}
std::unordered_map<std::string, std::string> HTMLParser::parseFiles(const std::string &str) {
  Extractor extractor { str, current_delim };
  std::unordered_map<std::string, std::string> result;
  for (; extractor.isLastBoundary(); extractor.moveOffset()) {
    result.emplace(parseFile(extractor));
  }

  return result;
}
std::pair<std::string, std::string> HTMLParser::parseFile(Extractor &extractor) {
  return { extractor.extract(Delims::name_matcher_beg, Delims::name_matcher_end),
           extractor.extract(Delims::file_matcher_beg, current_delim, 1) };  // Without the ending character
}

}  // namespace home::webserver