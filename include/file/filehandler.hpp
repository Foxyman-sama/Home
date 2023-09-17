#ifndef LOCALHOST_FILEMANAGER_INCLUDE_HPP
#define LOCALHOST_FILEMANAGER_INCLUDE_HPP

#include <fstream>
#include "core.hpp"

namespace local::host {
class FileHandler {
private:
    std::ifstream fin_;
    std::ofstream fout_;

public:
    void write(const std::string &_k_filename, const core::Data &_k_data);
    core::Data read(const std::string &_k_filename);
};
}

#endif
