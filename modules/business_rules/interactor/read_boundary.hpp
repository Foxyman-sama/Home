#ifndef HOME_READ_BOUNDARY_HPP
#define HOME_READ_BOUNDARY_HPP

#include "../business_rules_api.hpp"
#include "files.hpp"

namespace home::interactor {
class BRAPI ReadBoundary {
public:
  virtual Files readFiles(const std::vector<std::string> &) = 0;
};
}

#endif
