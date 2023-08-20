#ifndef LOCALHOST_JSON_INCLUDE_HPP
#define LOCALHOST_JSON_INCLUDE_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "utility/file.hpp"

namespace local::host {
class JSON {
public:
    std::pair<std::string, utility::File> parse(const core::Data &_k_data);
};
}

#endif
