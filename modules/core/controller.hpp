#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace home::controller {

class Controller {
 public:
  virtual std::unordered_map<std::string, std::string> save(const std::string &str) = 0;

  virtual std::vector<std::string> getSavedFilenames() = 0;
};

}  // namespace home::controller

#endif