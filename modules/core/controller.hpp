#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <vector>

#include "hash_table.hpp"

namespace home::controller {

class Controller {
 public:
  virtual HashTable<std::string, std::string> save(const std::string &str) = 0;
};

}  // namespace home::controller

#endif