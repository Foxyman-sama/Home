#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <vector>

namespace home::interactor {

class Container {
 public:
  virtual void write(const std::string &, const std::string &) = 0;

  virtual std::string read(const std::string &) = 0;
};

}  // namespace home::interactor

#endif