#ifndef HTML_FILES_GENERATOR_HPP
#define HTML_FILES_GENERATOR_HPP

#include <format>
#include <limits>
#include <random>
#include <string>

struct GeneratedParams {
  std::string data;
  size_t number_of_files = 0;
  size_t size_of_files = 0;
};

class HTMLMaker {
 private:
  GeneratedParams generated;

 public:
  void makeTextFileAndAppend(const std::string &filename, size_t size, const std::string &symbol) {
    ++generated.number_of_files;
    generated.size_of_files += size;
    appendBoundary();
    appendFilename(filename);
    generated.data.append(size, symbol[0]);
    generated.data.append(1, '\n');
  }

  void appendFile(const std::string &filename, const std::vector<char> &data) {
    ++generated.number_of_files;
    generated.size_of_files += data.size();
    appendBoundary();
    appendFilename(filename);
    for (auto &&ch : data) {
      generated.data.append(1, ch);
    }

    generated.data.append(1, '\n');
  }

  GeneratedParams getGeneratedParamsAndIfNotEmptyAddLastBounary() {
    if (generated.data.empty() == false) {
      appendBoundary();
    }

    return generated;
  }

  void clearGeneratedData() {
    generated.number_of_files = 0;
    generated.size_of_files = 0;
    generated.data.clear();
  }

 private:
  void appendBoundary() {
    generated.data.append(6, '-');
    generated.data.append("WebKitFormBoundary");
    generated.data.append(1, '\n');
  }
  void appendFilename(const std::string &filename) {
    generated.data.append("filename=\"");
    generated.data.append(filename);
    generated.data.append(1, '\"');
    generated.data.append("\r\n\r\n");
  }
};

#endif