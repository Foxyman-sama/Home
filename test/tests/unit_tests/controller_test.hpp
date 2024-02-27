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
  MOCK_METHOD((std::vector<std::string>), getSavedFilenames, (), (override));
};
class ControllerTest : public Test {
 public:
  ControllerImpl controller;
  MockInteractor interactor;
  MockParser parser;

  ControllerTest() : controller { interactor, parser } {}
};

TEST_F(ControllerTest, Save_call_parse_and_encode_and_save) {
  EXPECT_CALL(parser, parse(_));
  EXPECT_CALL(interactor, save(_));
  controller.save({});
}
TEST_F(ControllerTest, GetSavedFilenames_call_getSavedFilenames_from_interactor) {
  EXPECT_CALL(interactor, getSavedFilenames());
  controller.getSavedFilenames();
}
TEST_F(ControllerTest, Get_call_get_from_interactor) {
  EXPECT_CALL(interactor, get(_));
  controller.get("");
}

#endif