#ifndef ENTITIES_FILEMANIPULATOR_HPP
#define ENTITIES_FILEMANIPULATOR_HPP

#include <vector>
#include <string>
#include "../business_rules_api.hpp"

namespace home::entities {
class BRAPI FileManipulator {
public:
    virtual std::vector<char> readFile(const std::string &) = 0;
    virtual void writeFile(const std::string &, const std::vector<char> &) = 0;
};
}

#endif
