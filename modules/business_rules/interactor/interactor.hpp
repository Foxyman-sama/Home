#ifndef HOME_INTERACTOR_HPP
#define HOME_INTERACTOR_HPP

#include "../entities/readstreamfactory.hpp"
#include "../entities/writestreamfactory.hpp"
#include "boundary.hpp"

namespace home::interactor {
class Interactor
  : public Boundary {
private:
  std::string directory_path;
  entities::WriteStreamFactory &creator_write_stream;
  entities::ReadStreamFactory &creator_read_stream;

public:
  explicit Interactor(const std::string &directory_path, entities::WriteStreamFactory &creator_write_stream,
                      entities::ReadStreamFactory &creator_read_stream) 
    : directory_path { directory_path }, creator_write_stream { creator_write_stream }
    , creator_read_stream { creator_read_stream } { }
  void writeFiles(const InputData &input_data) override;
  OutputData readFiles(const InputData &input_data) override;
};
}

#endif
