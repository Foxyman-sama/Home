#include "entities.hpp"

namespace home::entities::read {
FileReadStream::FileReadStream(const std::string &filename) {
  tryOpen(filename);
}
void FileReadStream::tryOpen(const std::string &filename) {
  in_stream.open(filename);
  if (in_stream.is_open() == false) {
    throwException(filename);
  }
}
void FileReadStream::throwException(const std::string &filename) {
  throw std::exception { std::format("Can't open the file: {}", filename).c_str() };
}
size_t FileReadStream::readSize() {
  in_stream.seekg(0, in_stream.end);

  auto size { in_stream.tellg() };
  in_stream.seekg(0, in_stream.beg);
  return size;
}
std::vector<char> FileReadStream::readData(size_t size) {
  std::vector<char> result { };
  result.resize(size);
  in_stream.read(result.data(), size);
  return result;
}
std::vector<char> FileReadStream::read() {
  auto size { readSize() };
  return readData(size);
}
std::shared_ptr<ReadStream> FileReadStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<ReadStream> { new FileReadStream { filename } };
}
}
namespace home::entities::write {
FileWriteStream::FileWriteStream(const std::string &filename) {
  tryOpen(filename);
}
void FileWriteStream::tryOpen(const std::string &filename) {
  out_stream.open(filename);
  if (out_stream.is_open() == false) {
    throwException(filename);
  }
}
void FileWriteStream::throwException(const std::string &filename) {
  throw std::exception { std::format("Can't open the file: {}", filename).c_str() };
}
void FileWriteStream::write(const std::vector<char> &data) {
  out_stream.write(data.data(), data.size());
}
std::shared_ptr<WriteStream> FileWriteStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<WriteStream> { new FileWriteStream { filename } };
}
}
