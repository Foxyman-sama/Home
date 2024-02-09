#ifndef CONTROLLER_IMPL_HPP
#define CONTROLLER_IMPL_HPP

#include <algorithm>
#include <ranges>
#include <stdexcept>

#include "controller.hpp"
#include "interactor.hpp"
#include "parser.hpp"

namespace home::controller {

constexpr std::string_view title_number_of_files { "number_of_files" };
constexpr std::string_view title_amount_of_data { "amount_of_data" };

class ControllerImpl : public Controller {
 private:
  interactor::Interactor &interactor;
  Parser &parser;

 public:
  ControllerImpl(interactor::Interactor &interactor, Parser &parser) : interactor { interactor }, parser { parser } {}

  std::unordered_map<std::string, std::string> save(const std::string &str) override;

 private:
  std::unordered_map<std::string, std::string> trysaveFiles(const std::string &str);
  std::unordered_map<std::string, std::string> formatReturn(size_t number_of_files, size_t amount_of_data);
};

}  // namespace home::controller

#endif