#include "entities.hpp"

namespace home::entities {
namespace read {
FileReadStream::FileReadStream(const std::string &filename) {
  
}
std::vector<char> FileReadStream::read() {
  return { };
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
 
}
bool FileWriteStream::isOpen() const noexcept {
  return false;
}
std::shared_ptr<WriteStream> FileWriteStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<WriteStream> { new FileWriteStream { filename } };
}
}
}