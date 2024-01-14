#ifndef INTERACTOR_HPP
#define INTERACTOR_HPP

#include <string>
#include <vector>

#include "modules/core/hash_table.hpp"

namespace home::interactor {

class Interactor {
 public:
  virtual void encodeAndSave(const HashTable<std::string, std::vector<char>> &) = 0;

  virtual std::vector<char> decodeAndGet(const std::string &) = 0;
};

}  // namespace home::interactor

#endif