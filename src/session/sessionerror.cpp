#include "session/sessionerror.hpp"

namespace local::host {
bool SessionError::isError() const noexcept {
    return dcode_ != DeadCode::NOTDEAD;
}
void SessionError::checkOnError(const Responce &_k_responce) noexcept {
    if (_k_responce.size_ >= UnprocessedValue::sk_bad_size_) {
        dcode_ = DeadCode::BADSIZE;
    }
    else {
        dcode_ = DeadCode::NOTDEAD;
    }

}
const char *SessionError::what() const {
    if (dcode_ == DeadCode::BADSIZE) {
        return "Size is wrong";
    }

    return "Errors didn`t find";
}
}