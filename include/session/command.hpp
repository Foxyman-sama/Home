#ifndef LOCALHOST_COMMAND_SESSION_INCLUDE_HPP
#define LOCALHOST_COMMAND_SESSION_INCLUDE_HPP

namespace local::host {
enum class Command : unsigned char {
    NOTHING,
    SEND,
    RECEIVE
};
}

#endif
