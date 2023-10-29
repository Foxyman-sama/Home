#ifndef HOME_SERIALIZER_HPP
#define HOME_SERIALIZER_HPP

#include <vector>
#include "adapters_api.hpp"

namespace home::adapters {
class AdaptersAPI Serializer {
public:
  virtual std::vector<char> serialize(const std::vector<std::vector<char>> &) = 0;
};
}

#endif
