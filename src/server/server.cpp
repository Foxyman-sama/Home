#include "server/server.hpp"

namespace local::host {
Server::Server(unsigned short _port) noexcept
    : acceptor_ { core::g_io_context, core::Endpoint { core::TCP::v4(), _port } } { }
void Server::init() {
    acceptor_.async_accept([this](const core::Error &_k_e,
                                  core::Socket &&_socket) {
        std::make_shared<Session>(std::move(_socket))->handle();
        init();
    });
}
} 