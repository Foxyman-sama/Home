#ifndef LOCALHOST_SESSION_INCLUDE_HPP
#define LOCALHOST_SESSION_INCLUDE_HPP

#include <iostream>
#include "sessionhandler.hpp"
#include "ui/icontroller.hpp"
#include "debug/debug.hpp"
#include "core.hpp"

namespace local::host {
class Session
    : public std::enable_shared_from_this<Session> {
private:
    size_t id_;
    core::Socket socket_;
    SessionHandler shandler_;
    std::shared_ptr<ui::base::IController> p_contr_;

    void send();
    void receive();
    void close() noexcept;
    bool checkOnError(const core::Error &_k_e) noexcept;

public:
    explicit Session(core::Size _id, core::Socket &&_socket,
                     std::shared_ptr<ui::base::IController> _p_cntrl) noexcept;
    void handle();
};
}

#endif
