#ifndef LOCALHOST_FILEMANAGER_INCLUDE_HPP
#define LOCALHOST_FILEMANAGER_INCLUDE_HPP

#include <fstream>
#include "core.hpp"

namespace local::host {
class FileManager {
private:
    std::ifstream fin_;
    std::ofstream fout_;

public:
    void write(const std::string &_k_filename,
               const core::Data &_k_data) noexcept;
    core::Data read(const std::string &_k_filename) noexcept;
};
}

#endif
