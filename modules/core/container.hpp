#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <vector>

namespace home::container {

class Container {
 public:
  virtual void write(const std::string &filename, const std::string &filedata) = 0;

  virtual std::string read(const std::string &filename) = 0;

  virtual std::vector<std::string> getSavedFilenames() = 0;
};

}  // namespace home::container

#endif