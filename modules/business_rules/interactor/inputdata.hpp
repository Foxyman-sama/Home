#ifndef HOME_INPUT_DATA_HPP
#define HOME_INPUT_DATA_HPP

#include <variant>
#include <vector>
#include <string>
#include <unordered_map>

using VectorStrings = std::vector<std::string>;
using HashTableFiles = std::unordered_map<std::string, std::vector<char>>;

namespace home::interactor {
class InputData {
public:
  std::variant<HashTableFiles, VectorStrings> files;
};
}

#endif
