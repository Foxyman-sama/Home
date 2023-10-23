#ifndef HOME_READ_STREAM_FACTORY_HPP
#define HOME_READ_STREAM_FACTORY_HPP

#include <memory>
#include "readstream.hpp"
#include "../business_rules_api.hpp"

namespace home::entities {
class BRAPI ReadStreamFactory {
public:
  virtual std::shared_ptr<ReadStream> create(const std::string &) = 0;
};
}

#endif
