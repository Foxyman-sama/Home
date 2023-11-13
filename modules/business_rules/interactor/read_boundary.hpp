#ifndef HOME_READ_BOUNDARY_HPP
#define HOME_READ_BOUNDARY_HPP

#include <vector>
#include <string>
#include "../business_rules_api.hpp"

using Files = std::vector<std::pair<std::string, std::vector<char>>>;

namespace home::interactor {
class BRAPI ReadBoundary {
public:
  virtual Files readFiles(const std::vector<std::string> &) = 0;
};
}

#endif
