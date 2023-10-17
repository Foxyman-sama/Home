#ifndef ENTITIES_FILEMANIPULATOR_HPP
#define ENTITIES_FILEMANIPULATOR_HPP

#include <vector>
#include <string>
#include "entities_api.hpp"

namespace home::entities {
class EntitiesAPI FileManipulator {
public:
    virtual std::vector<char> readFile(const std::string &) = 0;
    virtual void writeFile(const std::string &, const std::vector<char> &) = 0;
};
}

#endif
