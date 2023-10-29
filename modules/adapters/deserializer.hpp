#ifndef HOME_DESERIALIZER_HPP
#define HOME_DESERIALIZER_HPP

#include <vector>
#include "adapters_api.hpp"

namespace home::adapters {
class AdaptersAPI Deserializer {
public:
  virtual std::vector<std::vector<char>> deserialize(const std::vector<char> &) = 0;
};
}

#endif
