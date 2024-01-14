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
  auto files { parser.parse(str) };
  interactor.encodeAndSave(files);
  return makeResult(files);
}
HashTable<std::string, std::string> ControllerImpl::makeResult(const HashTable<std::string, std::vector<char>> &files) {
  auto number_of_files { files.getSize() };
  auto amount_of_data { countTotalAmountOfData(files) };
  return { { "number_of_files", std::to_string(number_of_files) },
           { "size_of_files", std::to_string(amount_of_data) } };
}
size_t ControllerImpl::countTotalAmountOfData(const HashTable<std::string, std::vector<char>> &files) {
  auto result { 0 };
  std::ranges::for_each(files, [&](auto &&pair) { result += pair.second.size(); });
  return result;
}

}  // namespace home::controller