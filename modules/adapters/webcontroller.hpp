#ifndef HOME_WEB_CONTROLLER_HPP
#define HOME_WEB_CONTROLLER_HPP

#include "../business_rules/interactor/boundary.hpp"
#include "controller.hpp"
#include "jsonconverter.hpp"

namespace home::adapters::controller {
class AdaptersAPI WebController 
  : public Controller {
private:
  interactor::Boundary &boundary;
  JSONConverter &converter;

public:
  explicit WebController(interactor::Boundary &boundary, JSONConverter &converter) noexcept;
  std::optional<std::vector<char>> handle(const std::vector<char> &web_data) override;
};
}

#endif
