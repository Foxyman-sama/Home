#include "webcontroller.hpp"

namespace home::adapters::controller {
WebController::WebController(interactor::Boundary &boundary, JSONConverter &converter) noexcept
  : boundary { boundary }, converter { converter } { }
std::optional<std::vector<char>> WebController::handle(const std::vector<char> &web_data) {
  return std::optional<std::vector<char>>();
}
}