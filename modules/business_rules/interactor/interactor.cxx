#include "interactor.hpp"
#include "interactor.hpp"
#include "interactor.hpp"

namespace home::interactor {
Interactor::Interactor(const std::string &directory_path, entities::WriteStreamFactory &creator_write_stream,
                       entities::ReadStreamFactory &creator_read_stream) noexcept
  : directory_path { directory_path }, creator_write_stream { creator_write_stream }
  , creator_read_stream { creator_read_stream } { }
FilenameDataMap Interactor::getFilenamesAndData(const InputData &input_data) {
	FilenameDataMap filenames_and_data { std::get<FilenameDataMap>(input_data.files) };
  if (filenames_and_data.empty() == true) {
    throwException("Can't extract filenames and data");
  }

	return filenames_and_data;
}
FilenamesVector Interactor::getFilenames(const InputData &input_data) {
  FilenamesVector filenames { std::get<FilenamesVector>(input_data.files) };
  if (filenames.empty() == true) {
    throwException("Can't extract filenames");
  }

  return filenames;
}
void Interactor::checkFilename(const std::string &filename) {
  if (filename.empty() == true) {
    throwException("Bad filename");
  }
}
void Interactor::throwException(const std::string &text) { 
    throw std::exception { text.c_str() };
}
void Interactor::writeFiles(const InputData &input_data) {
  auto filename_data_map { getFilenamesAndData(input_data) };
  for (auto &&[filename, filedata]: filename_data_map) {
    checkFilename(filename);

    auto write_stream { creator_write_stream.create(filename) };
    write_stream->write(filedata);
  }
}
OutputData Interactor::readFiles(const InputData &input_data) {
  auto filenames { getFilenames(input_data) };
  FilenameDataMap files { };
  for (auto &&filename: filenames) {
    checkFilename(filename);

    auto read_stream { creator_read_stream.create(filename) };
    files[filename] = read_stream->read();
  }

  return OutputData { files };
}
}