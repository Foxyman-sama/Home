#include "server/server.hpp"

namespace local::host {
Server::Server(core::net::io_context &_io, unsigned short _port,
               std::shared_ptr<ui::base::IController> _p_cntr) noexcept
    : acceptor_ { _io, core::Endpoint { core::TCP::v4(), _port } }, counter_ { }
    , p_contr_ { _p_cntr} { }
void Server::start() {
    acceptor_.async_accept(
        [this](const core::Error &_k_e, core::Socket &&_socket) {
            if (!_k_e) {
                auto ip { _socket.remote_endpoint().address().to_string() };
                auto port { _socket.remote_endpoint().port() };
                p_contr_->addSessionToUI(counter_, std::move(ip), port);
                std::make_shared<Session>(
                    counter_++, std::move(_socket), p_contr_)->handle();
            }

            start();
        });
}
} 