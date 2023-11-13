#include "interactor.hpp"

namespace home::interactor {
Interactor::Interactor(const std::string &directory_path, ent::write::WriteStreamFactory &creator_write_stream,
                       ent::read::ReadStreamFactory &creator_read_stream) noexcept
  : directory_path { directory_path }, creator_write_stream { creator_write_stream }
  , creator_read_stream { creator_read_stream } { }
void Interactor::writeFiles(const Files &input_data) {
  if (input_data.empty() == true) {
    throw std::exception { "input_data is empty!" };
  }

  tryWriteFiles(input_data);
}
void Interactor::tryWriteFiles(const Files &files) {
  for (auto &&[filename, filedata]: files) {
    tryWriteFile(filename, filedata);
  }
}
void Interactor::tryWriteFile(const std::string &filename, const std::vector<char> &filedata) {
  checkFilename(filename);

  auto write_stream { creator_write_stream.create(filename) };
  write_stream->write(filedata);
}
Files Interactor::readFiles(const std::vector<std::string> &input_data) {
  if (input_data.empty() == true) {
    throw std::exception { "input_data is empty!" };
  }

  return tryReadFiles(input_data);
}
Files Interactor::tryReadFiles(const std::vector<std::string> &filenames) {
  Files readed_files { };
  readed_files.reserve(filenames.size());
  for (auto &&filename: filenames) {
    readed_files.emplace_back(std::make_pair(filename, tryReadFile(filename)));
  }

  return readed_files;
}
std::vector<char> Interactor::tryReadFile(const std::string &filename) {
  checkFilename(filename);

  auto read_stream { creator_read_stream.create(filename) };
  return read_stream->read();
}
void Interactor::checkFilename(const std::string &filename) {
  if (filename.empty() == true) {
    throwException("Bad filename");
  }
}
void Interactor::throwException(const std::string &text) {
  throw std::exception { text.c_str() };
}
}