#ifndef HOME_FILE_WRITE_STREAM_HPP
#define HOME_FILE_WRITE_STREAM_HPP

#include <fstream>
#include "writestream.hpp"

namespace home::entities {
class BRAPI FileWriteStream
  : public WriteStream {
private:
  std::ofstream out_stream;

  void throwException(const std::string &filename);
  void tryOpen(const std::string &filename);

public:
  explicit FileWriteStream(const std::string &filename);
  void write(const std::vector<char> &data) override;
};
}

#endif
