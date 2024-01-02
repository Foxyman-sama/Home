#include "controller_impl.hpp"

namespace home::controller {

HashTable<std::string, std::string> ControllerImpl::save(const std::string &str) {
  try {
    return trySave(str);
  } catch (...) {
    throw;
  }
}
HashTable<std::string, std::string> ControllerImpl::trySave(const std::string &str) {
  auto files { parse(str) };
  return makeResult(files);  // I LOVE YOU! You're my little girl :>>>
}
HashTable<std::string, std::vector<char>> ControllerImpl::parse(const std::string &str) { return parser.parse(str); }
HashTable<std::string, std::string> ControllerImpl::makeResult(const HashTable<std::string, std::vector<char>> &files) {
  std::unordered_map<std::string, std::string> result;
  auto number_of_files { files.size() };
  auto size_of_files { calculateGeneralSizeOfFiles(files) };
  result["number_of_files"] = std::to_string(number_of_files);
  result["size_of_files"] = std::to_string(size_of_files);
  return result;
}
size_t ControllerImpl::calculateGeneralSizeOfFiles(const HashTable<std::string, std::vector<char>> &files) {
  auto result { 0 };
  for (auto &&[filename, filedata] : files) {
    result += filedata.size();
  }

  return result;
}

}  // namespace home::controller