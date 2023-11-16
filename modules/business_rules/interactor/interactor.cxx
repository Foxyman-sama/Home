#include "interactor.hpp"

namespace home::interactor {
Interactor::Interactor(const std::string &directory_path, entities::write::WriteStreamFactory &write_stream_factory,
                       entities::read::ReadStreamFactory &read_stream_factory) noexcept
  : directory_path { directory_path }, write_stream_factory { write_stream_factory }
  , read_stream_factory { read_stream_factory } { }

void Interactor::writeFiles(const Files &input_data) {
  try {
    tryWriteFiles(input_data);
  }
  catch (const std::exception &) {
    // TO DO:
    // 1. Log to da
  }
}
void Interactor::tryWriteFiles(const Files &files) { 
  for (auto &&[filename, filedata]: files) { 
    tryWriteFile(filename, filedata);
  }
}
void Interactor::tryWriteFile(const std::string &filename, const std::vector<char> &filedata) { 
  write_stream_factory.create(filename)->write(filedata);
}

Files Interactor::readFiles(const std::vector<std::string> &input_data) {
  Files readed_files { tryReadFiles(input_data) };
  return readed_files;
}
Files Interactor::tryReadFiles(const  std::vector<std::string> &filenames) {
  Files readed_files { };
  for (auto &&filename: filenames) {
    readed_files.emplace_back(tryReadFile(filename));
  }

  return readed_files;
}
std::pair<std::string, std::vector<char>> Interactor::tryReadFile(const std::string &filename) {
  std::vector<char> readed_data { read_stream_factory.create(filename)->read() };
  return std::make_pair(filename, readed_data);
}
}