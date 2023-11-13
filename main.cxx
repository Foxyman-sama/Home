#include "config.h"

#ifdef Testing
#include <filesystem>
#include "test/tests.hpp"

int main(int _argc, char **_p_argv) {
    int return_code { startTests(_argc, _p_argv) };
    std::cin.ignore();
    std::cin.get();
    return return_code; 
}

#else 

#include "modules/business_rules/entities/filemanipulatorimpl.hpp"
#include "modules/business_rules/interactor/interactor.hpp"

int main(int _argc, char **_p_argv) {
    
}

#endif