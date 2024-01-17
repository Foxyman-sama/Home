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
  auto [number_of_files, amount_of_data] { interactor.encodeAndSave(files) };
  return formatReturn(number_of_files, amount_of_data);
}
HashTable<std::string, std::string> ControllerImpl::formatReturn(size_t number_of_files, size_t amount_of_data) {
  return { { title_number_of_files.data(), std::to_string(number_of_files) },
           { title_amount_of_data.data(), std::to_string(amount_of_data) } };
}

}  // namespace home::controller