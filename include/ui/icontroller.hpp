#ifndef LOCALHOST_ICONTROLLER_BASE_INCLUDE_HPP
#define LOCALHOST_ICONTROLLER_BASE_INCLUDE_HPP

#include "core.hpp"

namespace local::ui::base {
class IController {
public:
    virtual void addSessionToUI(core::Size _id, const std::string &_k_ip,
                                unsigned short _port) = 0;
    virtual void deleteSessionFromUI(core::Size _id) = 0;
    virtual void setSendStatus(core::Size _id) = 0;
    virtual void setReceiveStatus(core::Size _id) = 0;
    virtual void setHandleStatus(core::Size _id) = 0;
};
}

#endif
