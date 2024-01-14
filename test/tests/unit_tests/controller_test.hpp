#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "modules/core/controller_impl.hpp"

using namespace testing;
using namespace home;
using namespace controller;
using namespace interactor;

class MockParser : public Parser {
 public:
  MOCK_METHOD((HashTable<std::string, std::vector<char>>), parse, (const std::string &), (override));
};
class MockInteractor : public Interactor {
 public:
  MOCK_METHOD(void, encodeAndSave, ((const HashTable<std::string, std::vector<char>> &)), (override));
  MOCK_METHOD((std::vector<char>), decodeAndGet, (const std::string &), (override));
};

class ControllerTest : public Test {
 public:
  ControllerImpl controller;
  MockInteractor interactor;
  MockParser parser;

  ControllerTest() : controller { interactor, parser } {}
};

TEST_F(ControllerTest, Call_save_call_encode_and_save) {
  EXPECT_CALL(interactor, encodeAndSave(_));
  EXPECT_CALL(parser, parse(_));
  controller.save("");
}

#endif