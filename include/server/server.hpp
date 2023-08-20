#ifndef LOCALHOST_SERVER_INCLUDE_HPP
#define LOCALHOST_SERVER_INCLUDE_HPP

#include "core.hpp"
#include "session/session.hpp"

namespace local::host {
class Server {
private:
    core::Acceptor acceptor_;

public:
    explicit Server(unsigned short _port) noexcept;
    void init();
};
}

#endif
