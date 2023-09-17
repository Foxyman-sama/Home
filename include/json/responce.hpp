#ifndef LOCALHOST_RESPONCE_INCLUDE_HPP
#define LOCALHOST_RESPONCE_INCLUDE_HPP

#include "core.hpp"
#include "session/command.hpp"

namespace local::host {
class Responce {
public:
    std::string filename_;
    core::Data data_;
    core::Size size_;
    Command command_;
};
}

#endif
