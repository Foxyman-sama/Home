#include "filewritestreamfactory.hpp"

namespace home::entities {
std::shared_ptr<WriteStream> FileWriteStreamFactory::create(const std::string &filename) {
  return std::shared_ptr<WriteStream> { new FileWriteStream { filename } };
}
}