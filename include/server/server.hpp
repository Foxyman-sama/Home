#ifndef LOCALHOST_SERVER_INCLUDE_HPP
#define LOCALHOST_SERVER_INCLUDE_HPP

#include "socket.hpp"
#include "session/session.hpp"

namespace local::host {
class Server {
private:
    TCP::acceptor acceptor_;

public:
    explicit Server(unsigned short _port) noexcept;
    void start();
};
}

#endif
