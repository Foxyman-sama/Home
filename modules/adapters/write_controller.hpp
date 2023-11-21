#ifndef HOME_WRITE_CONTROLLER_API_HPP
#define HOME_WRITE_CONTROLLER_API_HPP

#include <vector>

namespace home::adapters {
class WriteController {
public:
  virtual void write(const std::vector<char> &) = 0;
};
}

#endif
