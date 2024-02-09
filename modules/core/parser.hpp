#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace home::controller {

class Parser {
 public:
  virtual std::unordered_map<std::string, std::string> parse(const std::string &str) = 0;
};

}  // namespace home::controller

#endif