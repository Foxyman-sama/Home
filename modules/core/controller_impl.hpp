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
  HashTable<std::string, std::string> formatReturn(size_t number_of_files, size_t amount_of_data);
};

}  // namespace home::controller

#endif