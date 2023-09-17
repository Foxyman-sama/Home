#ifndef LOCALHOST_JSON_INCLUDE_HPP
#define LOCALHOST_JSON_INCLUDE_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "responce.hpp"

namespace local::host {
namespace pt = boost::property_tree;

class JSONHandler {
public:
    Responce parse(const core::Data &_k_data);
};
}

#endif
