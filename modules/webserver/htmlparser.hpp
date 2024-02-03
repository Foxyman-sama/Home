#ifndef HTMLPARSER_HPP
#define HTMLPARSER_HPP

#include <stdexcept>
#include <string>

#include "../core/parser.hpp"
#include "html_definitions.hpp"

namespace home::webserver {

class HTMLParser : public controller::Parser {
 private:
  std::string_view current_delim;
  size_t offset;

 public:
  HashTable<std::string, std::string> parse(const std::string &str);

 private:
  HashTable<std::string, std::string> tryParse(const std::string &str);
  void selectBoundary(const std::string &str);
  bool isEnd(const std::string &src);
  std::pair<std::string, std::string> parseFile(const std::string &str);
  std::string parseFilename(const std::string &str);
  std::pair<size_t, size_t> find(const std::string &str, const std::string_view &start, const std::string_view &end);
  std::string extract(const std::string &str, size_t beg, size_t end);

  std::string parseData(const std::string &str);
};

}  // namespace
   // home::webserver

#endif