#ifndef HOME_WRITE_BOUNDARY_HPP
#define HOME_WRITE_BOUNDARY_HPP

#include <vector>
#include <string>
#include "../business_rules_api.hpp"

using Files = std::vector<std::pair<std::string, std::vector<char>>>;

namespace home::interactor {
class BRAPI WriteBoundary {
public:
  virtual void writeFiles(const Files &) = 0;
};
}

#endif
