#ifndef LOCALHOST_SESSIONHANDLER_INCLUDE_HPP
#define LOCALHOST_SESSIONHANDLER_INCLUDE_HPP

#include "core.hpp"
#include "json/jsonhandler.hpp"
#include "file/filehandler.hpp"
#include "json/responce.hpp"
#include "sessionerror.hpp"

namespace local::host {
class SessionHandler {
private:
    JSONHandler jhandler_;
    FileHandler fhandler_;
    Responce responce_;
    SessionError error_;

public:
    [[nodiscard]]
    core::Data &getData() noexcept;
    [[nodiscard]]
    core::Size &getSize() noexcept;
    [[nodiscard]]
    Command getCommand() const noexcept;
    void parse();
    void write();
    void read();
    void clear() noexcept;
    bool hasError() noexcept;
    const char *lastError() const noexcept;
};
}

#endif
