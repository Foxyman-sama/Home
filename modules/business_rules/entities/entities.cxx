#include "entities.hpp"

namespace home::entities {
namespace read {
FileReadStream::FileReadStream(const std::string &filename) {
  tryOpen(filename);
}
std::vector<char> FileReadStream::read() {
  return readData(readSize());
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
void FileReadStream::throwException(const std::string &filename) {
  throw std::exception { ("File: " + filename + " can't be opened").c_str() };
}
std::shared_ptr<ReadStream> FileReadStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<ReadStream> { new FileReadStream { filename } };
}
}
namespace write {
FileWriteStream::FileWriteStream(const std::string &filename) {
  tryOpen(filename);
}
void FileWriteStream::throwException(const std::string &filename) {
  throw std::exception { ("File: " + filename + " can't be opened").c_str() };
}
void FileWriteStream::tryOpen(const std::string &filename) {
  out_stream.open(filename);
  if (out_stream.is_open() == false) {
    throwException(filename);
  }
}
void FileWriteStream::write(const std::vector<char> &data) {
  out_stream.write(data.data(), data.size());
}
std::shared_ptr<WriteStream> FileWriteStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<WriteStream> { new FileWriteStream { filename } };
}
}
}