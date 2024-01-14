#ifndef INTERACTOR_IMPL_HPP
#define INTERACTOR_IMPL_HPP

#include "container.hpp"
#include "decoder_base64.hpp"
#include "encoder_base64.hpp"
#include "interactor.hpp"

namespace home::interactor {

class InteractorImpl : public Interactor {
 private:
  crypto::Base64Encoder &encoder;
  crypto::Base64Decoder &decoder;
  container::Container &container;

 public:
  InteractorImpl(crypto::Base64Encoder &encoder, crypto::Base64Decoder &decoder, container::Container &container);

  void encodeAndSave(const HashTable<std::string, std::vector<char>> &files) override;

  std::vector<char> decodeAndGet(const std::string &filename) override;
};

}  // namespace home::interactor

#endif