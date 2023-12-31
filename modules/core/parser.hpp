#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace home::controller {

template <typename Key, typename Value>
using HashTable = std::unordered_map<Key, Value>;

class Parser {
 public:
  virtual HashTable<std::string, std::vector<char>> parse(const std::string &str) = 0;
};

}  // namespace home::controller

#endif