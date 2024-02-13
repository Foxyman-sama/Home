#ifndef INTERACTOR_HPP
#define INTERACTOR_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace home::interactor {

class Interactor {
 public:
  virtual std::pair<size_t, size_t> save(const std::unordered_map<std::string, std::string> &) = 0;

  virtual std::string get(const std::string &) = 0;
};

}  // namespace home::interactor

#endif