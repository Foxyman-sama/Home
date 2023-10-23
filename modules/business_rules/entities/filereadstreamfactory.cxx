#include "filereadstreamfactory.hpp"

namespace home::entities {
std::shared_ptr<ReadStream> home::entities::FileReadStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<ReadStream> { new FileReadStream { filename } };
}

}
