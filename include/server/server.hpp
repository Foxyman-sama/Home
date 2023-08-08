#ifndef LOCALHOST_SERVER_INCLUDE_HPP
#define LOCALHOST_SERVER_INCLUDE_HPP

#include "socket.hpp"

namespace local::host {
using namespace network;

class Server {
private:
    using TCP = socket::base::TCP;

    void handle(socket::TCPSocket &&_socket);

    TCP::acceptor acceptor_;

public:
    explicit Server(unsigned short _port) noexcept
        : acceptor_ { socket::base::g_io_context, TCP::endpoint { TCP::v4(), _port } } { }

    void start();
};
}

#endif
