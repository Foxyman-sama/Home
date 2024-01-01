#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "hash_table.hpp"

namespace home::controller {

class Parser {
 public:
  virtual HashTable<std::string, std::vector<char>> parse(const std::string &str) = 0;
};

}  // namespace home::controller

#endif