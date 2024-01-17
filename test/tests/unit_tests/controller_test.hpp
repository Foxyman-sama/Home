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
  MOCK_METHOD((HashTable<std::string, std::string>), parse, (const std::string &), (override));
};
class MockInteractor : public Interactor {
 public:
  MOCK_METHOD((std::pair<size_t, size_t>), encodeAndSave, ((const HashTable<std::string, std::string> &)), (override));
  MOCK_METHOD((std::string), decodeAndGet, (const std::string &), (override));
};
class ControllerTest : public Test {
 public:
  ControllerImpl controller;
  MockInteractor interactor;
  MockParser parser;

  ControllerTest() : controller { interactor, parser } {}
};

TEST_F(ControllerTest, Call_save_call_parse_and_encode_and_save) {
  EXPECT_CALL(parser, parse(_));
  EXPECT_CALL(interactor, encodeAndSave(_));
  controller.save({});
}

#endif