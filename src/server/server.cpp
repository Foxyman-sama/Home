#include "server/server.hpp"

namespace local::host {
void Server::handle(socket::TCPSocket &&_socket) {
    while (true) {
        data::Data command { _socket.receive() };
    }
}
void Server::start() {
	try {
        while (true) {
            std::shared_ptr<socket::TCPSocket> p_socket { 
                new socket::TCPSocket { acceptor_.accept() } }
            ;
            std::jthread { [this, p_socket]() {
                this->handle(p_socket);
            } }
        }
    }
    catch (...) { }
}
}