#ifndef TEST_PARSER_HPP
#define TEST_PARSER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace controller;

class ParserTest : public Test {
 private:
  HTMLParser parser;
  std::string data;
  HashTable<std::string, std::string> expected_data;
  HashTable<std::string, std::string> actual_data;
  bool is_threw_exception;

 public:
  void givenNumberOfFilesAndMaxSize(size_t number_of_files, size_t max_size) {
    auto [tuple, files] { generateHTMLWithFiles<std::string, std::string>(number_of_files, max_size) };
    data = std::get<0>(tuple);
    expected_data = files;
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
TEST_F(ParserTest, Parsing_100_files_with_max_size_1_is_correct) {
  givenNumberOfFilesAndMaxSize(100, 1);
  whenParserIsParsing();
  thenActualShouldBeEqualExpected();
}
TEST_F(ParserTest, Parsing_100_files_with_max_size_1000_is_correct) {
  givenNumberOfFilesAndMaxSize(100, 1'000);
  whenParserIsParsing();
  thenActualShouldBeEqualExpected();
}

#endif