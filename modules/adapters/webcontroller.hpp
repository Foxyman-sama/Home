#ifndef HOME_WEB_CONTROLLER_HPP
#define HOME_WEB_CONTROLLER_HPP

#include "controller.hpp"

namespace home::adapters::controller {
class WebController 
  : public Controller {
public:


  std::optional<std::vector<char>> handle(const std::vector<char> &web_data) override;
};
}

#endif
