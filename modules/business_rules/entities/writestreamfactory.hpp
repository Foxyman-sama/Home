#ifndef HOME_WRITE_STREAM_FACTORY_HPP
#define HOME_WRITE_STREAM_FACTORY_HPP

#include <memory>
#include "writestream.hpp"
#include "../business_rules_api.hpp"

namespace home::entities {
class BRAPI WriteStreamFactory {
public:
	virtual std::shared_ptr<WriteStream> create(const std::string &) = 0;
};
}

#endif
