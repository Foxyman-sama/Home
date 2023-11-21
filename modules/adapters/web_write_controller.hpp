#ifndef HOME_WEB_WRITE_CONTROLLER_HPP
#define HOME_WEB_WRITE_CONTROLLER_HPP

#include "write_controller.hpp"
#include "deserializer.hpp"
#include "../business_rules/interactor/write_boundary.hpp"

namespace home::adapters {
class AdaptersAPI WebWriteController 
  : public WriteController {
private:
  interactor::WriteBoundary &boundary;
  Deserializer &deserializer;

public:
  WebWriteController(interactor::WriteBoundary &boundary, Deserializer &deserializer) noexcept
    : boundary { boundary }, deserializer { deserializer } { }

  void write(const std::vector<char> &web_data) override; 
};
}

#endif
