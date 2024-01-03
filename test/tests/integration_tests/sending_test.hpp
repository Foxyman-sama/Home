#ifndef INTEGRATION_TESTS_SENDING_TEST_HPP
#define INTEGRATION_TESTS_SENDING_TEST_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../generators/html_files_generator.hpp"
#include "modules/core/controller_impl.hpp"
#include "modules/webserver/htmlparser.hpp"
#include "reader.hpp"

using namespace testing;
using namespace home;
using namespace controller;
using namespace webserver;

class SendingTest : public Test {
 private:
  Reader reader;
  HTMLGenerator generator;

 public:
  std::string expected_data;
  size_t expected_number_of_files;
  size_t expected_size_of_files;

  void SetUp() override {
    reader.open("build/", "sending_test_input.txt");
    while (reader.isEndOfFile() == false) {
      std::string buffer { reader.readString() };
      if (buffer == "create") {
        createFile(reader);
      } else if (buffer == "append") {
        appendFile(reader);
      }
    }

    auto [data, number_of_files, size_of_files] { generator.getGeneratedParamsAndIfNotEmptyAddLastBounary() };
    expected_data = data;
    expected_number_of_files = number_of_files;
    expected_size_of_files = size_of_files;
    generator.clearGeneratedData();
  }

 private:
  void createFile(Reader &reader) {
    auto filename { reader.readString() };
    auto size { reader.readNumber() };
    auto symbol { reader.readString() };
    expected_size_of_files += size;
    generator.makeTextFileAndAppend(filename, size, symbol);
  }

  void appendFile(Reader &reader) {
    auto filename { reader.readString() };
    auto binary_data { reader.createStreamAndReadFile(filename) };
    expected_size_of_files += binary_data.size();
    generator.appendFile(filename, binary_data);
  }
};

TEST_F(SendingTest, Sending_web_data_and_using_html_parser) {
  HTMLParser parser;
  ControllerImpl controller { parser };
  auto actual_result { controller.save(expected_data) };
  ASSERT_EQ(std::stoi(actual_result.at("number_of_files")), expected_number_of_files);
  ASSERT_EQ(std::stoi(actual_result.at("size_of_files")), expected_size_of_files);
}

#endif