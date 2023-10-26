#ifndef HOME_BOUNDARY_HPP
#define HOME_BOUNDARY_HPP

#include "inputdata.hpp"
#include "outputdata.hpp"

namespace home::interactor {
  class BRAPI Boundary {
  public:
    virtual void writeFiles(const InputData &) = 0;
    virtual OutputData readFiles(const InputData &) = 0;
  };
}

#endif
