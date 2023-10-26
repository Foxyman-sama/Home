#ifndef HOME_INTERACTOR_DEFINITIONS_HPP
#define HOME_INTERACTOR_DEFINITIONS_HPP

#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include "../business_rules_api.hpp"

namespace home::interactor {
class BRAPI FilenamesVector
  : public std::vector<std::string> { };
class BRAPI FilenameDataMap
  : public  std::unordered_map<std::string, std::vector<char>> { };
class BRAPI FileVariant
  : public std::variant<FilenameDataMap, FilenamesVector> { };
}

#endif
