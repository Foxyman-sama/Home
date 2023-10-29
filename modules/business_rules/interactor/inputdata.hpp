#ifndef HOME_INPUT_DATA_HPP
#define HOME_INPUT_DATA_HPP

#include <variant>
#include "definitions.hpp"

namespace home::interactor {
class __declspec(dllexport) InputData {
public:
  FileVariant files;
};
}

#endif
