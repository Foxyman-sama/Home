#ifndef HOME_FILE_READ_STREAM_HPP
#define HOME_FILE_READ_STREAM_HPP

#include <fstream>
#include "readstream.hpp"

namespace home::entities {
class BRAPI FileReadStream
  : public ReadStream {
private:
  std::ifstream in_stream;

  void throwException(const std::string &filename);
  void tryOpen(const std::string &filename);
  size_t readSize();
  std::vector<char> readData(size_t size);

public:
  explicit FileReadStream(const std::string &filename);
  std::vector<char> read() override;
};
}

#endif
