#ifndef HOME_INTERACTOR_HPP
#define HOME_INTERACTOR_HPP

#include "../entities/entities.hpp"
#include "boundary.hpp"

namespace home::interactor {
namespace ent = home::entities;

class BRAPI Interactor
  : public Boundary {
private:

private:
  std::string directory_path;
  ent::write::WriteStreamFactory &creator_write_stream;
  ent::read::ReadStreamFactory &creator_read_stream;

  Files tryReadFiles(const std::vector<std::string> &filenames);
  std::vector<char> tryReadFile(const std::string &filename);

  void tryWriteFiles(const Files &files);
  void tryWriteFile(const std::string &filename, const std::vector<char> &filedata);

  void checkFilename(const std::string &filename);
  void throwException(const std::string &text);

public:
  explicit Interactor(const std::string &directory_path, ent::write::WriteStreamFactory &creator_write_stream,
                      ent::read::ReadStreamFactory &creator_read_stream) noexcept;

  void writeFiles(const Files &input_data) override;

  Files readFiles(const std::vector<std::string> &input_data) override;
};
}

#endif
