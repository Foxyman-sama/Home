#include "json/jsonhandler.hpp"

namespace local::host {
Responce JSONHandler::parse(const core::Data &_k_data) {
    std::stringstream ss { };
    ss << _k_data.data();

    pt::ptree root { };
    pt::read_json(ss, root);

    Responce responce { };
    responce.command_ = Command { root.get<unsigned char>("command") };
    responce.filename_ = root.get<std::string>("name");
    responce.size_ = root.get<core::Size>("size");
    return responce;
}
}