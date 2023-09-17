#include "ui/controller.hpp"

namespace local::ui {
Controller::Controller() noexcept
    : ui_ { UI::getUI() } { }
void Controller::addSessionToUI(core::Size _id, const std::string &_k_ip,
                                unsigned short _port) {
    DisplayedConnection dc { _id, _k_ip, std::to_string(_port), "Handle" };
    ui_.addSessionToUI(std::move(dc));
}
void Controller::deleteSessionFromUI(core::Size _id) {
    ui_.deleteSessionFromUI(_id);
}
void Controller::setSendStatus(core::Size _id) {
    ui_.changeSessionStatus(_id, "Send");
}
void Controller::setReceiveStatus(core::Size _id) { 
    ui_.changeSessionStatus(_id, "Receive");
}
void Controller::setHandleStatus(core::Size _id) { 
    ui_.changeSessionStatus(_id, "Handle");
}
}