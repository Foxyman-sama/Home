#ifndef LOCALHOST_STATUS_UI_INCLUDE_HPP
#define LOCALHOST_STATUS_UI_INCLUDE_HPP

namespace local::ui {
enum class Status : unsigned char {
    HANDLE,
    RECEIVE,
    SEND
};
}

#endif
