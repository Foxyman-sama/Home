#ifndef HOME_OUTPUT_DATA_HPP
#define HOME_OUTPUT_DATA_HPP

#include <variant>
#include "definitions.hpp"

namespace home::interactor {
class __declspec(dllexport) OutputData {
public:
  FileVariant files;
};
}

#endif
