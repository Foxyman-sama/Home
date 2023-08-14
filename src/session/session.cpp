#include "session/session.hpp"

namespace local::host {
Session::Session(TCP::socket &&_socket) noexcept
    : socket_ { std::move(_socket) } { }
void Session::handle() { }
}