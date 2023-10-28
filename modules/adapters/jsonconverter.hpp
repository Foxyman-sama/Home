#ifndef HOME_JSONCONVERTER_HPP
#define HOME_JSONCONVERTER_HPP

#include "adapters_api.hpp"
#include "json.hpp"

namespace home::adapters {
class AdaptersAPI JSONConverter {
public:
  virtual JSON convert(const std::vector<char> &) = 0;
};
}

#endif
