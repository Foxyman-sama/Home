#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "parser.hpp"

namespace home::controller {

template <typename Key, typename Value>
using HashTable = std::unordered_map<Key, Value>;

class Controller {
 public:
  virtual HashTable<std::string, std::string> save(const std::string &str) = 0;
};
class ControllerImpl : public Controller {
 private:
  Parser &parser;

 public:
  ControllerImpl(Parser &parser) : parser { parser } {}

  HashTable<std::string, std::string> save(const std::string &str) override;

 private:
  HashTable<std::string, std::vector<char>> parse(const std::string &str);
};

}  // namespace home::controller

#endif