#include "session/sessionhandler.hpp"

namespace local::host {
core::Data &SessionHandler::getData() noexcept {
    return responce_.data_;
}
core::Size &SessionHandler::getSize() noexcept {
    return responce_.size_;
}
Command SessionHandler::getCommand() const noexcept {
    return responce_.command_;
}
void SessionHandler::parse() {
    responce_ = jhandler_.parse(responce_.data_);
    responce_.data_.resize(responce_.size_);
}
void SessionHandler::write() {
    fhandler_.write(responce_.filename_, responce_.data_);
}
void SessionHandler::read() {
    responce_.data_ = fhandler_.read(responce_.filename_);
    responce_.size_ = responce_.data_.size();
}
void SessionHandler::clear() noexcept {
    responce_.command_ = Command { };
    responce_.data_.clear();
    responce_.filename_.clear();
    responce_.size_ = 0;
}
bool SessionHandler::hasError() noexcept {
    error_.checkOnError(responce_);
    return error_.isError();
}
const char *SessionHandler::lastError() const noexcept {
    return error_.what();
}
}