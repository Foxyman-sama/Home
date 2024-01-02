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

 public:
  HTMLParser parser;

  void givenData(const std::string& data, HashTable<std::string, std::vector<char>> expected) { this->data = data; }
  void whenParserIsParsing() {
    try {
      actual_data = parser.parse(data);
    } catch (...) {
    }
  }
  void thenActualShouldBeEqualExpected() { ASSERT_EQ(actual_data, expected_data); }
};

TEST_F(ParserTest, Parser_parse_correctly) {}

#endif