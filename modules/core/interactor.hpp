#ifndef INTERACTOR_HPP
#define INTERACTOR_HPP

#include <string>
#include <vector>

#include "modules/core/hash_table.hpp"

namespace home::interactor {

class Interactor {
 public:
  virtual std::pair<size_t, size_t> encodeAndSave(const HashTable<std::string, std::string> &) = 0;

  virtual std::string decodeAndGet(const std::string &) = 0;
};

}  // namespace home::interactor

#endif