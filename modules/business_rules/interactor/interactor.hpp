#ifndef HOME_INTERACTOR_HPP
#define HOME_INTERACTOR_HPP

#include "../entities/entities.hpp"
#include "read_boundary.hpp"
#include "write_boundary.hpp"

namespace home::interactor {
class BRAPI Interactor
  : public ReadBoundary
  , public WriteBoundary {
  std::string directory_path;
  entities::write::WriteStreamFactory &creator_write_stream;
  entities::read::ReadStreamFactory &creator_read_stream;

public:
  explicit Interactor(const std::string &directory_path, entities::write::WriteStreamFactory &creator_write_stream,
                      entities::read::ReadStreamFactory &creator_read_stream) noexcept;

  void writeFiles(const Files &input_data) override;

  Files readFiles(const std::vector<std::string> &input_data) override;
};
}

#endif
