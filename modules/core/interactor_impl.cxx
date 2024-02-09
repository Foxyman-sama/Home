#include "interactor_impl.hpp"

namespace home::interactor {

InteractorImpl::InteractorImpl(container::JSONContainer &container) : container { container } {}

std::pair<size_t, size_t> InteractorImpl::save(const std::unordered_map<std::string, std::string> &files) {
  try {
    return trysaveFilesFiles(files);
  } catch (...) {
    throw;
  }
}
std::pair<size_t, size_t> InteractorImpl::trysaveFilesFiles(const std::unordered_map<std::string, std::string> &files) {
  DataCounter counter;
  for (auto &&[filename, filedata] : files) {
    saveFilesFile(filename, filedata);
    counter.count(filedata);
  }

  return counter.get();
}
void InteractorImpl::saveFilesFile(const std::string &filename, const std::string &filedata) {
  container.write(encoder.encode(filename), encoder.encode(filedata));
}

std::string InteractorImpl::get(const std::string &filename) {
  try {
    return trygetFile(filename);
  } catch (...) {
    throw;
  }
}
std::string InteractorImpl::trygetFile(const std::string &filename) {
  auto encoded_filename { encoder.encode(filename) };
  auto encoded { container.read(encoded_filename) };
  return decoder.decode(encoded);
}

}  // namespace home::interactor