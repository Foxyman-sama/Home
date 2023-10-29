#ifndef HOME_WEB_CONTROLLER_HPP
#define HOME_WEB_CONTROLLER_HPP

#include "../business_rules/interactor/boundary.hpp"
#include "controller.hpp"
#include "jsonconverter.hpp"
#include "serializer.hpp"
#include "deserializer.hpp"

namespace home::adapters {
class AdaptersAPI WebController 
  : public Controller {
private:
  interactor::Boundary &boundary;
  JSONConverter &converter;
  Serializer &serializer;
  Deserializer &deserializer;

public:
  explicit WebController(interactor::Boundary &boundary, JSONConverter &converter, Serializer &serializer, 
                         Deserializer &deserializer) noexcept;
  std::optional<std::vector<char>> handle(const std::vector<char> &web_data) override;
};
}

#endif
