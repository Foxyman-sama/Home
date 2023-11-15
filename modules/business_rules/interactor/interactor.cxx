#include "interactor.hpp"

namespace home::interactor {
Interactor::Interactor(const std::string &directory_path, entities::write::WriteStreamFactory &creator_write_stream,
                       entities::read::ReadStreamFactory &creator_read_stream) noexcept
  : directory_path { directory_path }, creator_write_stream { creator_write_stream }
  , creator_read_stream { creator_read_stream } { }
void Interactor::writeFiles(const Files &input_data) { }

Files Interactor::readFiles(const std::vector<std::string> &input_data) {
  return { };
}
}