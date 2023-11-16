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
  entities::write::WriteStreamFactory &write_stream_factory;
  entities::read::ReadStreamFactory &read_stream_factory;

  void tryWriteFiles(const Files &files);
  void tryWriteFile(const std::string &filename, const std::vector<char> &filedata);

  Files tryReadFiles(const std::vector<std::string> &filenames);
  std::pair<std::string, std::vector<char>> tryReadFile(const std::string &filename);

public:
  explicit Interactor(const std::string &directory_path, entities::write::WriteStreamFactory &write_stream_factory,
                      entities::read::ReadStreamFactory &read_stream_factory) noexcept;

  void writeFiles(const Files &input_data) override;

  Files readFiles(const std::vector<std::string> &input_data) override;
};
}

#endif
