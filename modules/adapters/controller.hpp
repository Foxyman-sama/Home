#ifndef HOME_CONTROLLER_HPP
#define HOME_CONTROLLER_HPP

#include <vector>
#include <optional>
#include "adapters_api.hpp"

namespace home::adapters {
class AdaptersAPI Controller {
public:
  virtual std::optional<std::vector<char>> handle(const std::vector<char> &) = 0;
};
}

#endif
