#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include "test_base.hpp"

class MockParser : public Parser {
 public:
  MOCK_METHOD((std::unordered_map<std::string, std::string>), parse, (const std::string &), (override));
};
class MockInteractor : public Interactor {
 public:
  MOCK_METHOD((std::pair<size_t, size_t>), save, ((const std::unordered_map<std::string, std::string> &)), (override));
  MOCK_METHOD((std::string), get, (const std::string &), (override));
};
class ControllerTest : public Test {
 public:
  ControllerImpl controller;
  MockInteractor interactor;
  MockParser parser;

  ControllerTest() : controller { interactor, parser } {}
};

TEST_F(ControllerTest, Call_saveFiles_call_parse_and_encode_and_saveFiles) {
  EXPECT_CALL(parser, parse(_));
  EXPECT_CALL(interactor, save(_));
  controller.save({});
}

#endif