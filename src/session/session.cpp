#include "session/session.hpp"

namespace local::host {
Session::Session(core::Socket &&_socket) noexcept
    : socket_ { std::move(_socket) }
    , file_ { } { }
void Session::send() { 
    auto p_self { shared_from_this() };
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(&file_.size_, sizeof(core::Size)),
        [this, p_self](const core::Error &_k_e,
                       size_t) {
            if (_k_e) {
                close();
                return;
            }

            boost::asio::async_write(
                socket_,
                boost::asio::buffer(file_.data_, file_.size_),
                [this, p_self](const core::Error &_k_e,
                               size_t) {
                    if (_k_e) {
                        close();
                        return;
                    }

                    handle();
                });
        });
}
void Session::receive() { 
    auto p_self { shared_from_this() };
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(&file_.size_, sizeof(core::Size)),
        [this, p_self](const core::Error &_k_e,
                       size_t) {
            if (_k_e) {
                close();
                return;
            }

            file_.data_.resize(file_.size_);
            boost::asio::async_read(
                socket_,
                boost::asio::buffer(file_.data_, file_.size_),
                [this, p_self](const core::Error &_k_e,
                               size_t) {
                    if (_k_e) {
                        close();
                        return;
                    }

                    filemanager_.write(file_.filename_, file_.data_);
                    handle();
                });
        });
}
void Session::close() noexcept { 
    core::Error error { };
    socket_.shutdown(socket_.shutdown_both, error);
    socket_.close();
}
void Session::handle() {
    auto p_self { shared_from_this() };
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(&file_.size_, sizeof(core::Size)),
        [this, p_self](const core::Error &_k_e,
                       size_t) {
            if (_k_e) {
                close();
                return;
            }

            file_.data_.resize(file_.size_);
            boost::asio::async_read(
                socket_,
                boost::asio::buffer(file_.data_.data(), file_.size_),
                [this, p_self](const core::Error &_k_e,
                               size_t) {
                    if (_k_e) {
                        close();
                        return;
                    }

                    auto [command, file] { parser_.parse(file_.data_) };
                    file_ = std::move(file);
                    if (command == Commands::k_receive_command_) {
                        receive();
                    }
                    else if (command == Commands::k_send_command_)  {
                        file_.data_ = filemanager_.read(file_.filename_);
                        file_.size_ = file_.data_.size();
                        send();
                    }
                });
        });
}
}