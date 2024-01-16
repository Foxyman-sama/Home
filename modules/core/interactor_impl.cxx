#include "interactor_impl.hpp"

namespace home::interactor {

InteractorImpl::InteractorImpl(crypto::Base64Encoder &encoder, crypto::Base64Decoder &decoder,
                               container::Container &container)
    : encoder { encoder }, decoder { decoder }, container { container } {}

std::pair<size_t, size_t> InteractorImpl::encodeAndSave(const HashTable<std::string, std::vector<char>> &files) {
  try {
    return tryEncodeAndSaveFiles(files);
  } catch (...) {
    throw;
  }
}
std::pair<size_t, size_t> InteractorImpl::tryEncodeAndSaveFiles(
    const HashTable<std::string, std::vector<char>> &files) {
  DataCounter counter;
  for (auto &&[filename, filedata] : files) {
    encodeAndSaveFile(filename, filedata);
    counter.count(filedata);
  }

  return counter.get();
}
void InteractorImpl::encodeAndSaveFile(const std::string &filename, const std::vector<char> &filedata) {
  auto encoded { encoder.encode(filedata) };
  auto encoded_filename { encoder.encode(Converter::stringToVector(filename)) };
  container.write(Converter::vectorToString(encoded_filename), Converter::vectorToString(encoded));
}

std::vector<char> InteractorImpl::decodeAndGet(const std::string &filename) {
  try {
    return tryDecodeAndGet(filename);
  } catch (...) {
    throw;
  }
}
std::vector<char> InteractorImpl::tryDecodeAndGet(const std::string &filename) {
  auto encoded_filename { encoder.encode(filename) };
  auto encoded { container.read(encoded_filename) };
  return Converter::stringToVector(decoder.decode(encoded));
}

}  // namespace home::interactor