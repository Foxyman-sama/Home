#ifndef LOCALHOST_SESSION_INCLUDE_HPP
#define LOCALHOST_SESSION_INCLUDE_HPP

#include <boost/bind/bind.hpp>
#include "core.hpp"
#include "json/json.hpp"
#include "filemanager/filemanager.hpp"

namespace local::host {
class Commands {
public:
    static constexpr std::string_view k_receive_command_ { "receive" };
    static constexpr std::string_view k_send_command_ { "send" };
};
class Session
    : public std::enable_shared_from_this<Session> {
private:
    core::Socket socket_;
    utility::File file_;
    JSON parser_;
    FileManager filemanager_;

    void send();
    void receive();
    void close() noexcept;

public:
    explicit Session(core::Socket &&_socket) noexcept;
    void handle();
};
}

#endif
