#ifndef HOME_SERIALIZER_HPP
#define HOME_SERIALIZER_HPP

#include "../business_rules/interactor/files.hpp"

namespace home::adapters {
class Serializer {
public:
  virtual std::vector<char> serialize(const interactor::Files &) = 0;
};
}

#endif
