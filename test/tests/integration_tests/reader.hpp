#ifndef READER_HPP
#define READER_HPP

#include <fstream>

class Reader {
 private:
  std::fstream fin;
  std::string folder;

 public:
  void open(const std::string &folder, const std::string &path) {
    this->folder = folder;
    fin.open(folder + path);
  }

  bool isOpen() { return fin.is_open(); }
  bool isEndOfFile() { return fin.peek() == EOF; };

  std::string readString() {
    std::string result;
    fin >> result;
    return result;
  }
  int readNumber() {
    std::string result;
    fin >> result;
    return std::stoi(result);
  }

  std::vector<char> readFile(const std::string &filename) {
    std::ifstream file_stream { folder + filename, std::ios_base::binary };
    file_stream.seekg(0, file_stream.end);

    auto size { file_stream.tellg() };
    file_stream.seekg(0, file_stream.beg);

    std::vector<char> result(size);
    file_stream.read(result.data(), size);
    return result;
  }
};

#endif