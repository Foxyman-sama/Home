#ifndef HOME_FILE_READ_STREAM_FACTORY_HPP
#define HOME_FILE_READ_STREAM_FACTORY_HPP

#include "filereadstream.hpp"
#include "readstreamfactory.hpp"

namespace home::entities {
class BRAPI FileReadStreamFactory 
  : public ReadStreamFactory {
public:
  std::shared_ptr<ReadStream> create(const std::string &filename) override;
};
}

#endif
