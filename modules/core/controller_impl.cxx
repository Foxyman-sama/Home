#include "controller_impl.hpp"

namespace home::controller {

HashTable<std::string, std::string> ControllerImpl::save(const std::string &str) {
  auto files { parse(str) };
  std::unordered_map<std::string, std::string> result;
  auto number_of_files { 0 };
  auto size_of_files { 0 };
  for (auto &&[name, data] : files) {
    ++number_of_files;
    size_of_files += data.size();
  }

  result["number_of_files"] = std::to_string(number_of_files);
  result["size_of_files"] = std::to_string(size_of_files);
  return result;
}
HashTable<std::string, std::vector<char>> ControllerImpl::parse(const std::string &str) { return parser.parse(str); }

}  // namespace home::controller