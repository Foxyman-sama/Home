#ifndef HOME_FILE_WRITE_STREAM_FACTORY_HPP
#define HOME_FILE_WRITE_STREAM_FACTORY_HPP

#include "filewritestream.hpp"
#include "writestreamfactory.hpp"

namespace home::entities {
class BRAPI FileWriteStreamFactory
  : public WriteStreamFactory {
public:
  std::shared_ptr<WriteStream> create(const std::string &filename) override;
};
}

#endif
