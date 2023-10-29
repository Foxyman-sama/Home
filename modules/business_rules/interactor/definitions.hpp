#ifndef HOME_INTERACTOR_DEFINITIONS_HPP
#define HOME_INTERACTOR_DEFINITIONS_HPP

#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include "../business_rules_api.hpp"

namespace home::interactor {
class __declspec(dllexport) FilenamesVector
  : public std::vector<std::string> { };
class __declspec(dllexport) FilenameDataMap
  : public  std::unordered_map<std::string, std::vector<char>> { };
class __declspec(dllexport) FileVariant
  : public std::variant<FilenameDataMap, FilenamesVector> { };
}

#endif
