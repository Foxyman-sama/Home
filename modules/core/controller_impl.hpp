#ifndef CONTROLLER_IMPL_HPP
#define CONTROLLER_IMPL_HPP

#include <stdexcept>

#include "controller.hpp"
#include "parser.hpp"

namespace home::controller {

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