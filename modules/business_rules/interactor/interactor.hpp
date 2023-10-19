#ifndef INTERACTOR_INTERACTOR_HPP
#define INTERACTOR_INTERACTOR_HPP

#include <stdexcept>
#include "ioboundary.hpp"
#include "../entities/filemanipulator.hpp"
#include "../business_rules_api.hpp"

namespace home::interactor {
class BRAPI UseCaseInteractor 
    : public IOBoundary {
private:
    using VectorString = std::vector<std::string>;

    entities::FileManipulator &fmanipulator_;

public:
    explicit UseCaseInteractor(entities::FileManipulator &_fmanipulator) noexcept
        : fmanipulator_ { _fmanipulator } { }
    void writeFiles(const HashTableFiles &_k_files) override;
    std::vector<char> readFiles(const VectorString &_k_filenames) override;
};
}

#endif
