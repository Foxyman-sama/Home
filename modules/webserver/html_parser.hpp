#ifndef HTML_PARSER_HPP
#define HTML_PARSER_HPP

#include <stdexcept>
#include <string>

#include "../core/parser.hpp"
#include "html_definitions.hpp"

namespace home::webserver {

class Extractor {
 private:
  const std::string &str;
  const std::string_view &boundary;
  size_t offset;

 public:
  explicit Extractor(const std::string &str, const std::string_view &boundary);

  std::string extract(const std::string_view &beg, const std::string_view &end, size_t right_offset = 0);

  void moveOffset();

  bool isLastBoundary() const noexcept;

 private:
  std::pair<size_t, size_t> find(const std::string_view &beg, const std::string_view &end);

  size_t getFileNextOffset() const noexcept;
};

class HTMLParser : public controller::Parser {
 private:
  std::string_view current_delim;

 public:
  std::unordered_map<std::string, std::string> parse(const std::string &str);

 private:
  std::unordered_map<std::string, std::string> tryParse(const std::string &str);
  void selectBoundary(const std::string &str);
  const bool isBoundaryFound(const std::string &str, const std::string_view &boundary) const noexcept;
  std::unordered_map<std::string, std::string> parseFiles(const std::string &str);
  std::pair<std::string, std::string> parseFile(Extractor &extractor);
};

}  // namespace home::webserver

#endif