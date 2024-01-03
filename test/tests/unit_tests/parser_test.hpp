#ifndef TEST_PARSER_HPP
#define TEST_PARSER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "modules/webserver/htmlparser.hpp"

using namespace testing;
using namespace home;
using namespace controller;

class ParserTest : public Test {
 private:
  std::string data;
  HashTable<std::string, std::vector<char>> expected_data;
  HashTable<std::string, std::vector<char>> actual_data;
  bool is_threw_exception;

 public:
  HTMLParser parser;

  void givenNumberOfFilesAndMaxSize(size_t number_of_files, size_t max_size) {
    auto generated_data { fastGenerate(number_of_files, max_size) };
    data = generated_data.first.data;
    expected_data = generated_data.second;
    is_threw_exception = false;
  }
  void whenParserIsParsing() {
    try {
      actual_data = parser.parse(data);
    } catch (...) {
      is_threw_exception = true;
    }
  }
  void thenActualShouldBeEqualExpected() { ASSERT_EQ(actual_data, expected_data); }
  void thenParserShouldThrowException() { ASSERT_EQ(is_threw_exception, true); }
};

TEST_F(ParserTest, Parsing_empty_throws_exception) {
  givenNumberOfFilesAndMaxSize(0, 0);
  whenParserIsParsing();
  thenParserShouldThrowException();
}
TEST_F(ParserTest, Parsing_100_files_with_max_size_1000_is_correct) {
  givenNumberOfFilesAndMaxSize(100, 1000);
  whenParserIsParsing();
  thenActualShouldBeEqualExpected();
}

#endif