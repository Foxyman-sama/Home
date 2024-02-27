#include "interactor_impl.hpp"

namespace home::interactor {

InteractorImpl::InteractorImpl(container::Container &container) : container { container } {}

std::pair<size_t, size_t> InteractorImpl::save(const std::unordered_map<std::string, std::string> &files) {
  try {
    return trySave(files);
  } catch (...) {
    throw std::runtime_error { "Interactor::save error." };
  }
}
std::pair<size_t, size_t> InteractorImpl::trySave(const std::unordered_map<std::string, std::string> &files) {
  DataCounter counter;
  for (auto &&[filename, filedata] : files) {
    saveFile(filename, filedata);
    counter.count(filedata);
  }

  return counter.get();
}
void InteractorImpl::saveFile(const std::string &filename, const std::string &filedata) {
  container.write(encoder.encode(filename), encoder.encode(filedata));
}

std::string InteractorImpl::get(const std::string &filename) {
  try {
    return tryGet(filename);
  } catch (...) {
    throw std::runtime_error { "Interactor::get error." };
  }
}
std::string InteractorImpl::tryGet(const std::string &filename) {
  auto encoded_filename { encoder.encode(filename) };
  auto encoded { container.read(encoded_filename) };
  return decoder.decode(encoded);
}

}  // namespace home::interactor