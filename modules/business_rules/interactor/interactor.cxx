#include "interactor.hpp"

namespace home::interactor {
void UseCaseInteractor::writeFiles(const HashTableFiles &_k_files) {
    if (_k_files.empty() == true) {
        throw std::runtime_error { "Bad data" };
    }

    for (auto &&[fname, fdata]: _k_files) {
        fmanipulator_.writeFile(fname, fdata);
    }
}
std::vector<char> UseCaseInteractor::readFiles(const VectorString &_k_filenames) {
    if (_k_filenames.empty() == true) {
        throw std::runtime_error { "Bad data" };
    }

    return std::vector<char>();
}
}
