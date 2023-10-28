#ifndef HOME_INTERACTOR_HPP
#define HOME_INTERACTOR_HPP

#include "../entities/readstreamfactory.hpp"
#include "../entities/writestreamfactory.hpp"
#include "boundary.hpp"

namespace home::interactor {
class BRAPI Interactor
  : public Boundary {
private:
  std::string directory_path;
  entities::WriteStreamFactory &creator_write_stream;
  entities::ReadStreamFactory &creator_read_stream;

  FilenameDataMap getFilenamesAndData(const InputData &input_data);
  FilenamesVector getFilenames(const InputData &input_data);
  FilenameDataMap tryReadFiles(const std::vector<std::string> &filenames);
  std::vector<char> tryReadFile(const std::string &filename);
  void tryWriteFiles(const FilenameDataMap &files);
  void tryWriteFile(const std::string &filename, const std::vector<char> &filedata);
  void checkFilename(const std::string &filename);
  void throwException(const std::string &text);

public:
  explicit Interactor(const std::string &directory_path, entities::WriteStreamFactory &creator_write_stream,
                      entities::ReadStreamFactory &creator_read_stream) noexcept;
  void writeFiles(const InputData &input_data) override;
  OutputData readFiles(const InputData &input_data) override;
};
}

#endif
