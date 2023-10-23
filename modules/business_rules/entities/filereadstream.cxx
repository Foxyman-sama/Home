#include "filereadstream.hpp"

namespace home::entities {
FileReadStream::FileReadStream(const std::string &filename) {
  tryOpen(filename);
}
void FileReadStream::throwException(const std::string &filename) {
  throw std::exception { ("File: " + filename + " can't be opened").c_str() };
}
void FileReadStream::tryOpen(const std::string &filename) {
  in_stream.open(filename);
  if (in_stream.is_open() == false) {
    throwException(filename);
  }
}
size_t FileReadStream::readSize() {
  in_stream.seekg(0, in_stream.end);

  auto file_size { in_stream.tellg() };
  in_stream.seekg(0, in_stream.beg);
  return file_size;
}
std::vector<char> FileReadStream::readData(size_t size) {
  std::vector<char> file_data { };
  file_data.resize(size);
  in_stream.read(file_data.data(), size);
  return file_data;
}
std::vector<char> FileReadStream::read() {
  return readData(readSize());
}
}