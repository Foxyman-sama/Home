#include "filewritestream.hpp"

namespace home::entities {
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
}