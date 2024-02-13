#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include "test_base.hpp"

class MockContainer : public JSONContainer {
 public:
  MOCK_METHOD(void, write, (const std::string &, const std::string &), (override));
  MOCK_METHOD((std::string), read, (const std::string &), (override));
};

class InteractorTest : public Test {
 public:
  InteractorImpl interactor;
  MockContainer container;

  InteractorTest() : interactor { container } {}
};

TEST_F(InteractorTest, Save_call_write) {
  EXPECT_CALL(container, write(_, _));
  interactor.save({ { "", "" } });
}
TEST_F(InteractorTest, Get_call_read) {
  EXPECT_CALL(container, read(_));
  interactor.get("");
}

#endif