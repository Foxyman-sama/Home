#ifndef INTERACTOR_IMPL_HPP
#define INTERACTOR_IMPL_HPP

#include <ranges>

#include "../utility/converter.hpp"
#include "container.hpp"
#include "decoder_base64.hpp"
#include "encoder_base64.hpp"
#include "interactor.hpp"

namespace home::interactor {

class DataCounter {
 private:
  size_t number_of_files { 0 };
  size_t amount_of_data { 0 };

 public:
  void count(const std::vector<char> &data) noexcept {
    number_of_files += 1;
    amount_of_data += data.size();
  }

  std::pair<size_t, size_t> get() const noexcept { return { number_of_files, amount_of_data }; }
};
class InteractorImpl : public Interactor {
 private:
  crypto::Base64Encoder &encoder;
  crypto::Base64Decoder &decoder;
  container::Container &container;

 public:
  InteractorImpl(crypto::Base64Encoder &encoder, crypto::Base64Decoder &decoder, container::Container &container);

  std::pair<size_t, size_t> encodeAndSave(const HashTable<std::string, std::vector<char>> &files) override;

  std::vector<char> decodeAndGet(const std::string &filename) override;

 private:
  std::pair<size_t, size_t> tryEncodeAndSaveFiles(const HashTable<std::string, std::vector<char>> &files);
  void encodeAndSaveFile(const std::string &filename, const std::vector<char> &filedata);
  std::string vectorToString(const std::vector<char> &vec) noexcept;

  std::vector<char> tryDecodeAndGet(const std::string &filename);
};

}  // namespace home::interactor

#endif