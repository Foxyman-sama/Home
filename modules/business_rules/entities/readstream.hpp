#ifndef HOME_READ_STREAM_HPP
#define HOME_READ_STREAM_HPP

#include <string>
#include <vector>
#include "../business_rules_api.hpp"

namespace home::entities {
class BRAPI ReadStream {
public:
    virtual std::vector<char> read() = 0;
};
}

#endif
