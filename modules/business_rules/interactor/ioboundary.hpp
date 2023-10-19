#ifndef INTERACTOR_IOBOUNDARY_HPP
#define INTERACTOR_IOBOUNDARY_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "../business_rules_api.hpp"

namespace home::interactor {
class BRAPI IOBoundary {
protected:
    using HashTableFiles = std::unordered_map<std::string, std::vector<char>>;

public:
    virtual void writeFiles(const HashTableFiles &) = 0;
    virtual std::vector<char> readFiles(const std::vector<std::string> &) = 0;
};
}

#endif
