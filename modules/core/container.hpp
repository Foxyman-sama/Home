#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <vector>

namespace home::container {

class Container {
 public:
  virtual void write(const std::string &, const std::string &) = 0;

  virtual std::string read(const std::string &) = 0;
};

}  // namespace home::container

#endif