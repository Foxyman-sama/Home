#ifndef HTML_FILES_GENERATOR_HPP
#define HTML_FILES_GENERATOR_HPP

#include <format>
#include <limits>
#include <random>
#include <string>

class HTMLMaker {
 private:
  std::string data;
  size_t number_of_files = 0;
  size_t size_of_files = 0;

 public:
  void makeTextFileAndAppend(const std::string &filename, size_t size, const std::string &symbol) {
    ++number_of_files;
    size_of_files += size;
    appendBoundary();
    appendFilename(filename);
    data.append(size, symbol[0]);
    data.append(1, '\n');
  }

  void appendFile(const std::string &filename, const std::string &str) {
    ++number_of_files;
    size_of_files += str.size();
    appendBoundary();
    appendFilename(filename);
    for (auto &&ch : str) {
      data.append(1, ch);
    }

    data.append(1, '\n');
  }

  std::tuple<std::string, size_t, size_t> getFileGeneratedParamsAndIfNotEmptyAddLastBounary() {
    if (data.empty() == false) {
      appendBoundary();
    }

    return { data, number_of_files, size_of_files };
  }

  void clearGeneratedData() {
    number_of_files = 0;
    size_of_files = 0;
    data.clear();
  }

 private:
  void appendBoundary() {
    data.append(6, '-');
    data.append("WebKitFormBoundary");
    data.append(1, '\n');
  }
  void appendFilename(const std::string &filename) {
    data.append("filename=\"");
    data.append(filename);
    data.append(1, '\"');
    data.append("\r\n\r\n");
  }
};

#endif