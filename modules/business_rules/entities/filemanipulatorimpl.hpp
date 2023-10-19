#ifndef ENTITIES_FILEMANIPULATOR_IMPL_HPP
#define ENTITIES_FILEMANIPULATOR_IMPL_HPP

#include <fstream>
#include "filemanipulator.hpp"

namespace home::entities {
class BRAPI FileManipulatorImpl
    : public FileManipulator {
private:
    std::fstream filemanipulator_;

public:
    std::vector<char> readFile(const std::string &_k_filename) override;
    void writeFile(const std::string &_k_filename,
                   const std::vector<char> &_k_data) override;
};
}

#endif
