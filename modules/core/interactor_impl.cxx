#include "interactor_impl.hpp"

namespace home::interactor {

InteractorImpl::InteractorImpl(crypto::Base64Encoder &encoder, crypto::Base64Decoder &decoder,
                               container::Container &container)
    : encoder { encoder }, decoder { decoder }, container { container } {}

void InteractorImpl::encodeAndSave(const HashTable<std::string, std::vector<char>> &files) {
  for (auto &&[filename, filedata] : files) {
    auto encoded { encoder.encode(filedata) };
    std::string temp;
    std::copy(std::begin(encoded), std::end(encoded), std::back_inserter(temp));
    container.write(filename, temp);
  }
}

std::vector<char> InteractorImpl::decodeAndGet(const std::string &filename) {
  auto encoded { container.read(filename) };
  std::vector<char> temp;
  std::copy(encoded.begin(), encoded.end(), temp.end());
  auto decoded { decoder.decode(temp) };
  return decoded;
}

}  // namespace home::interactor