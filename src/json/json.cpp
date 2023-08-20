#include "json/json.hpp"

namespace local::host {
std::pair<std::string, utility::File> JSON::parse(const core::Data &_k_data) {
    namespace pt = boost::property_tree;
    
    std::stringstream ss { };
    ss << _k_data.data();

    pt::ptree root { };
    pt::read_json(ss, root);
    
    utility::File file { };
    std::string command { root.get<std::string>("command") };
    file.filename_ = root.get<std::string>("filename");

    auto is_found { root.find("size") };
    if (is_found != root.not_found()) {
        file.size_ = root.get<core::Size>("size");
    }

    return std::pair { command, file };
}
}