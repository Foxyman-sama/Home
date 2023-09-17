#include "session/session.hpp"

namespace local::host {
Session::Session(core::Size _id, core::Socket &&_socket,
                 std::shared_ptr<ui::base::IController> _p_cntrl) noexcept
    : id_ { _id }, socket_ { std::move(_socket) }, p_contr_ { _p_cntrl } { }
void Session::send() { 
    p_contr_->setSendStatus(id_);
    shandler_.read();

    auto p_self { shared_from_this() };
    auto &size { shandler_.getSize() };
    auto &data { shandler_.getData() };
    boost::asio::async_write(
        socket_, boost::asio::buffer(&size, sizeof(core::Size)),
        [this, p_self, &data](const core::Error &_k_e, size_t) {
            if (checkOnError(_k_e)) {
                return;
            }

            boost::asio::async_write(
                socket_, boost::asio::buffer(data, data.size()),
                [this, p_self](const core::Error &_k_e, size_t) {
                    if (checkOnError(_k_e)) {
                        return;
                    }

                    handle();
                });
        });
}
void Session::receive() { 
    p_contr_->setReceiveStatus(id_);

    auto p_self { shared_from_this() };
    auto &size { shandler_.getSize() };
    auto &data { shandler_.getData() };
    boost::asio::async_read(
        socket_, boost::asio::buffer(data, size),
        [this, p_self](const core::Error &_k_e, size_t) {
            if (checkOnError(_k_e)) {
                return;
            }

            shandler_.write();
            handle();
        });
}
void Session::close() noexcept { 
    core::Error error { };
    socket_.shutdown(socket_.shutdown_both, error);
    socket_.close();
    p_contr_->deleteSessionFromUI(id_);
}
bool Session::checkOnError(const core::Error &_k_e) noexcept { 
    if (_k_e) {
        utility::Debug::debug(
            '(', socket_.remote_endpoint().address().to_string() + ":",
            socket_.remote_endpoint().port(), ") ", _k_e.message());
        close();
        return true;
    }
    else if (shandler_.hasError() == true) {
        utility::Debug::debug(
            '(', socket_.remote_endpoint().address().to_string() + ":",
            socket_.remote_endpoint().port(), ") ", shandler_.lastError());
        close();
        return true;
    }

    return false;
}
void Session::handle() {
    shandler_.clear();
    p_contr_->setHandleStatus(id_);

    auto p_self { shared_from_this() };
    auto &size { shandler_.getSize() };
    boost::asio::async_read(
        socket_, boost::asio::buffer(&size, sizeof(core::Size)),
        [this, p_self](const core::Error &_k_e, size_t) {
            if (checkOnError(_k_e) == true) {
                return;
            }    

            auto &data { shandler_.getData() };
            data.resize(shandler_.getSize());
            boost::asio::async_read(
                socket_, boost::asio::buffer(data, data.size()),
                [this, p_self](const core::Error &_k_e, size_t) {
                    if (checkOnError(_k_e) == true) {
                        return;
                    }

                    shandler_.parse();

                    auto command { shandler_.getCommand() };
                    if (command == Command::RECEIVE) {
                        receive();
                        return;
                    }
                    if (command == Command::SEND) {
                        send();
                        return;
                    }
                });
        });
}
}