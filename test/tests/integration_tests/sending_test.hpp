#ifndef INTEGRATION_TESTS_SENDING_TEST_HPP
#define INTEGRATION_TESTS_SENDING_TEST_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace testing;

class Parser {
 private:
  size_t offset;
  static constexpr std::string_view name_matcher_beg { "filename=\"" };
  static constexpr std::string_view name_matcher_end { "\"" };
  static constexpr std::string_view data_matcher_beg { "\r\n\r\n" };
  static constexpr std::string_view delim { "------WebKitFormBoundary" };

 public:
  std::unordered_map<std::string, std::vector<char>> parse(const std::string &str) {
    std::unordered_map<std::string, std::vector<char>> result;
    try {
      result = tryParse(str);
    } catch (...) {
      throw;
    }

    return result;
  }

 private:
  std::unordered_map<std::string, std::vector<char>> tryParse(const std::string &str) {
    std::unordered_map<std::string, std::vector<char>> result;
    for (offset = str.find(delim); isLastBoundary(str) == false; offset = str.find(delim, offset + delim.size())) {
      result.emplace(parseFile(str));
    }

    return result;
  }
  bool isLastBoundary(const std::string &src) { return src.find(delim, offset + 1) == std::string::npos; }
  std::pair<std::string, std::vector<char>> parseFile(const std::string &str) {
    auto filename { parseFilename(str) };
    auto data { parseData(str) };
    return { filename, data };
  }
  std::string parseFilename(const std::string &str) {
    auto [pos_beg, pos_end] { find(str, name_matcher_beg, name_matcher_end) };
    return extract(str, pos_beg, pos_end);
  }
  std::pair<size_t, size_t> find(const std::string &str, const std::string_view &start, const std::string_view &end) {
    auto pos_beg { str.find(start, offset) + start.length() };
    auto pos_end { str.find(end, pos_beg) };
    return { pos_beg, pos_end };
  }
  std::string extract(const std::string &str, size_t beg, size_t end) { return str.substr(beg, end - beg); }

  std::vector<char> parseData(const std::string &str) {
    auto [pos_beg, pos_end] { find(str, data_matcher_beg, delim) };
    auto pos_end_without_ending_character { pos_end - 1 };
    auto data { extract(str, pos_beg, pos_end_without_ending_character) };
    return stringToVector(data);
  }
  std::vector<char> stringToVector(const std::string &src) {
    std::vector<char> result;
    result.reserve(src.size());
    for (auto &&ch : src) {
      result.emplace_back(ch);
    }

    return result;
  }
};
class ControllerImpl {
 private:
  Parser parser;

 public:
  std::unordered_map<std::string, std::string> save(const std::string &data) {
    auto files { parse(data) };
    std::unordered_map<std::string, std::string> result;
    auto number_of_files { 0 };
    auto size_of_files { 0 };
    for (auto &&[name, data] : files) {
      ++number_of_files;
      size_of_files += data.size();
    }

    result["number_of_files"] = std::to_string(number_of_files);
    result["size_of_files"] = std::to_string(size_of_files);
    return result;
  }

 private:
  std::unordered_map<std::string, std::vector<char>> parse(const std::string &data) { return parser.parse(data); }
};
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
  void TearDown() override {}

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
  ControllerImpl controller;
  auto actual_result { controller.save(generated_data) };
  ASSERT_EQ(std::stoi(actual_result["number_of_files"]), expected_number_of_files);
  ASSERT_EQ(std::stoi(actual_result["size_of_files"]), expected_size_of_files);
}

#endif