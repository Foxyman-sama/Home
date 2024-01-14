#ifndef CONTROLLER_IMPL_HPP
#define CONTROLLER_IMPL_HPP

#include <algorithm>
#include <ranges>
#include <stdexcept>

#include "controller.hpp"
#include "modules/core/interactor.hpp"
#include "parser.hpp"

namespace home::controller {

class ControllerImpl : public Controller {
 private:
  Parser &parser;
  interactor::Interactor &interactor;

 public:
  ControllerImpl(interactor::Interactor &interactor, Parser &parser) : interactor { interactor }, parser { parser } {}

  HashTable<std::string, std::string> save(const std::string &str) override;

 private:
  HashTable<std::string, std::string> trySave(const std::string &str);
  HashTable<std::string, std::string> makeResult(const HashTable<std::string, std::vector<char>> &files);
  size_t countTotalAmountOfData(const HashTable<std::string, std::vector<char>> &files);
};

}  // namespace home::controller

#endif