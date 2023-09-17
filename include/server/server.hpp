#ifndef LOCALHOST_SERVER_INCLUDE_HPP
#define LOCALHOST_SERVER_INCLUDE_HPP

#include "core.hpp"
#include "session/session.hpp"
#include "ui/icontroller.hpp"

namespace local::host {
class Server {
private:
    core::Acceptor acceptor_;
    size_t counter_;
    std::shared_ptr<ui::base::IController> p_contr_;

public:
    explicit Server(core::net::io_context &_io, unsigned short _port,
                    std::shared_ptr<ui::base::IController> _p_cntrl) noexcept;
    void start();
};
}

#endif
