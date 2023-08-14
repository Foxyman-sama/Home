#include "server/server.hpp"

namespace local::host {
Server::Server(unsigned short _port) noexcept
    : acceptor_ { socket::base::g_io_context, TCP::endpoint { TCP::v4(), _port } } { }
void Server::start() {
	try {
        while (true) {
            acceptor_.async_accept([this](const boost::system::error_code &_k_ec,
                                          TCP::socket &&_socket) {
                std::make_shared<Session>(std::move(_socket))->handle();
                this->start();
            });
        }
    }
    catch (...) { }
}
}