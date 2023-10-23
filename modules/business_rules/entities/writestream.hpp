#ifndef HOME_WRITE_STREAM_HPP
#define HOME_WRITE_STREAM_HPP

#include <string>
#include <vector>
#include "../business_rules_api.hpp"

namespace home::entities {
class BRAPI WriteStream {
public:
    virtual void write(const std::vector<char> &) = 0;
};
}

#endif
