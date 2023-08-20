#ifndef LOCALHOST_UTILITY_FILE_INCLUDE_HPP
#define LOCALHOST_UTILITY_FILE_INCLUDE_HPP

#include <string>
#include "core.hpp"

namespace local::host::utility {
class File {
public:
    std::string filename_;
    core::Size size_;
    core::Data data_;
};
}

#endif
