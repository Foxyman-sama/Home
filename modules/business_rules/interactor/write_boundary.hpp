#ifndef HOME_WRITE_BOUNDARY_HPP
#define HOME_WRITE_BOUNDARY_HPP

#include "../business_rules_api.hpp"
#include "files.hpp"

namespace home::interactor {
class BRAPI WriteBoundary {
public:
  virtual void writeFiles(const Files &) = 0;
};
}

#endif
