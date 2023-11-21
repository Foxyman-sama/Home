#ifndef HOME_DESERIALIZER_HPP
#define HOME_DESERIALIZER_HPP

#include "../business_rules/interactor/files.hpp"
#include "adapters_api.hpp"

namespace home::adapters {
class AdaptersAPI Deserializer {
public:
  virtual interactor::Files deserialize(const std::vector<char> &) = 0;
};
}

#endif
