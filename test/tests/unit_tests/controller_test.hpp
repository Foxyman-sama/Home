#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "modules/core/controller_impl.hpp"

using namespace testing;
using namespace home;
using namespace controller;

class MockParser : public Parser {
 public:
  MOCK_METHOD((HashTable<std::string, std::vector<char>>), parse, (const std::string &), (override));
};
class ControllerTest : public Test {
 private:
  MockParser parser;
  std::unique_ptr<ControllerImpl> controller;
  std::string data;
  bool is_threw_exception;

 public:
  void SetUp() override {
    is_threw_exception = false;
    controller.reset(new ControllerImpl { parser });
  }

  void givenNumberOfCallOfParse(size_t num) { EXPECT_CALL(parser, parse).Times(num); }
  void whenControllerIsSaving() {
    try {
      controller->save(data);
    } catch (...) {
      is_threw_exception = true;
    }
  }
  void thenControllerShouldNotThrowException() { ASSERT_EQ(is_threw_exception, false); }
};

TEST_F(ControllerTest, Call_parse_one_time) {
  givenNumberOfCallOfParse(1);
  whenControllerIsSaving();
  thenControllerShouldNotThrowException();
}

#endif