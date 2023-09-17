#ifndef LOCALHOST_CONTROLLER_INCLUDE_HPP
#define LOCALHOST_CONTROLLER_INCLUDE_HPP

#include "ui.hpp"
#include "displayed_connection.hpp"
#include "icontroller.hpp"

namespace local::ui {
class Controller 
    : public base::IController {
private:
    UI &ui_;

public:
    Controller() noexcept;
    void addSessionToUI(core::Size _id, const std::string &_k_ip,
                        unsigned short _port) override;
    void deleteSessionFromUI(core::Size _id) override;
    void setSendStatus(core::Size _id) override;
    void setReceiveStatus(core::Size _id) override;
    void setHandleStatus(core::Size _id) override;
};
}

#endif
