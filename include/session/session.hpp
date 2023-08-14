#ifndef LOCALHOST_SESSION_INCLUDE_HPP
#define LOCALHOST_SESSION_INCLUDE_HPP

#include "socket.hpp"

using namespace network;

using TCP = socket::base::TCP;

namespace local::host {
class Session {
private:
    TCP::socket socket_;

public:
    explicit Session(TCP::socket &&_socket) noexcept;
    void handle();
};
}

#endif
