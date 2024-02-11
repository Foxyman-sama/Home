#ifndef INTERACTOR_IMPL_HPP
#define INTERACTOR_IMPL_HPP

#include <ranges>

#include "decoder_base64.hpp"
#include "encoder_base64.hpp"
#include "interactor.hpp"
#include "json_container.hpp"

namespace home::interactor {

class DataCounter {
 private:
  size_t number_of_files { 0 };
  size_t amount_of_str { 0 };

 public:
  void count(const std::string &str) noexcept {
    number_of_files += 1;
    amount_of_str += str.size();
  }

  std::pair<size_t, size_t> get() const noexcept { return { number_of_files, amount_of_str }; }
};

class InteractorImpl : public Interactor {
 private:
  crypto::Base64Encoder encoder;
  crypto::Base64Decoder decoder;
  container::JSONContainer &container;

 public:
  InteractorImpl(container::JSONContainer &container);

  std::pair<size_t, size_t> save(const std::unordered_map<std::string, std::string> &files) override;

  std::string get(const std::string &filename) override;

 private:
  std::pair<size_t, size_t> trysaveFilesFiles(const std::unordered_map<std::string, std::string> &files);
  void saveFilesFile(const std::string &filename, const std::string &filedata);

  std::string trygetFile(const std::string &filename);
};

}  // namespace home::interactor

#endif