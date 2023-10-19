#include "filemanipulatorimpl.hpp"

namespace home::entities {
std::vector<char> FileManipulatorImpl::readFile(const std::string &_k_filename) {
    if (_k_filename.empty() == true) {
        throw std::runtime_error { "Bad filename: " + _k_filename };
    }

    filemanipulator_.open(_k_filename, std::ios_base::in);
    if (filemanipulator_.is_open() == false) {
        throw std::runtime_error { "Bad filename: " + _k_filename };
    }

    filemanipulator_.seekg(0, filemanipulator_.end);

    size_t size { static_cast<size_t>(filemanipulator_.tellg()) }; 
    filemanipulator_.seekg(0, filemanipulator_.beg);

    std::vector<char> data { };
    data.resize(size);
    filemanipulator_.read(data.data(), size);
    filemanipulator_.close();
    return data;
}
void FileManipulatorImpl::writeFile(const std::string &_k_filename, 
                                    const std::vector<char> &_k_data) {
    if (_k_filename.empty() == true) {
        throw std::runtime_error { "Bad filename: " + _k_filename };
    }
    if (_k_data.empty() == true) {
        throw std::runtime_error { "Bad data" };
    }
    
    filemanipulator_.open(_k_filename, std::ios_base::out);
    filemanipulator_.write(_k_data.data(), _k_data.size());
    filemanipulator_.close();
}
}