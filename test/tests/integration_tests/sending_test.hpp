#ifndef INTEGRATION_TESTS_SENDING_TEST_HPP
#define INTEGRATION_TESTS_SENDING_TEST_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>

#include "modules/core/controller.hpp"
#include "modules/webserver/htmlparser.hpp"

using namespace testing;
using namespace home;
using namespace controller;
using namespace webserver;

class SendingTest : public Test {
 public:
  std::string generated_data;
  size_t expected_number_of_files;
  size_t expected_size_of_files;

  void SetUp() override {
    expected_number_of_files = 0;
    expected_size_of_files = 0;

    std::ifstream fin { "build/sending_test_input.txt" };
    std::string buffer;
    while (fin >> buffer) {
      ++expected_number_of_files;
      if (buffer == "create") {
        createFile(fin);
      } else if (buffer == "append") {
        appendFile(fin);
      }
    }

    addUnderLines();
  }

 private:
  void createFile(std::ifstream &fin) {
    std::string filename;
    fin >> filename;

    std::string size_in_str;
    fin >> size_in_str;

    std::string symbol;
    fin >> symbol;
    addUnderLines();
    addFilename(filename);

    auto size { std::stoi(size_in_str) };
    expected_size_of_files += size;
    generated_data.append(size, symbol[0]);
    generated_data.append(1, '\n');
  }
  void addUnderLines() {
    generated_data.append(6, '-');
    generated_data.append("WebKitFormBoundary");
    generated_data.append(1, '\n');
  }
  void addFilename(const std::string &filename) {
    generated_data.append("filename=\"");
    generated_data.append(filename);
    generated_data.append(1, '\"');
    generated_data.append("\r\n\r\n");
  }

  void appendFile(std::ifstream &fin) {
    std::string filename;
    fin >> filename;

    auto binary_data { readBinaryData(filename) };
    expected_size_of_files += binary_data.size();
    addUnderLines();
    addFilename(filename);
    for (auto &&ch : binary_data) {
      generated_data.append(1, ch);
    }

    generated_data.append(1, '\n');
  }
  std::vector<char> readBinaryData(const std::string &filename) {
    std::ifstream file_stream { "build/" + filename, std::ios_base::binary };
    file_stream.seekg(0, file_stream.end);

    auto size { file_stream.tellg() };
    file_stream.seekg(0, file_stream.beg);

    std::vector<char> result(size);
    file_stream.read(result.data(), size);
    return result;
  }
};

TEST_F(SendingTest, Sending) {
  HTMLParser parser;
  ControllerImpl controller { parser };
  auto actual_result { controller.save(generated_data) };
  ASSERT_EQ(std::stoi(actual_result["number_of_files"]), expected_number_of_files);
  ASSERT_EQ(std::stoi(actual_result["size_of_files"]), expected_size_of_files);
}

#endif