#ifndef LOCALHOST_DISPLAYED_CONNECTION_INCLUDE_HPP
#define LOCALHOST_DISPLAYED_CONNECTION_INCLUDE_HPP

#include <string>
#include "status.hpp"
#include "core.hpp"

namespace local::ui {
class DisplayedConnection {
public:
    core::Size id_;
    std::string address_;
    std::string port_;
    std::string status_;
};
}

#endif
