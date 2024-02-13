#ifndef READER_HPP
#define READER_HPP

#include <fstream>

std::string readFile(std::string path) {
  std::ifstream file_stream { path, std::ios_base::binary };
  file_stream.seekg(0, file_stream.end);

  const auto size { file_stream.tellg() };
  file_stream.seekg(0, file_stream.beg);

  std::string result(size, '\0');
  file_stream.read(result.data(), size);
  return result;
}

#endif