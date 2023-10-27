#ifndef HOME_CONTROLLER_HPP
#define HOME_CONTROLLER_HPP

#include <vector>
#include <optional>

namespace home::adapters::controller {
class Controller {
public:
  virtual std::optional<std::vector<char>> handle(const std::vector<char> &) = 0;
};
}

#endif
