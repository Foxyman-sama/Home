#include "filemanager/filemanager.hpp"

namespace local::host {
void FileManager::write(const std::string &_k_filename,
                        const core::Data &_k_data) noexcept { 
    fout_.open(_k_filename, std::ios_base::binary);
    fout_.write(_k_data.data(), _k_data.size());
    fout_.close();
}
core::Data FileManager::read(const std::string &_k_filename) noexcept {
    fin_.open(_k_filename, std::ios_base::binary);
    fin_.seekg(0, fin_.end);

    size_t size { static_cast<size_t>(fin_.tellg()) };
    fin_.seekg(0, fin_.beg);

    core::Data binary_data { };
    binary_data.resize(size);
    fin_.read(binary_data.data(), size);
    fin_.close();
    return binary_data;
}
}