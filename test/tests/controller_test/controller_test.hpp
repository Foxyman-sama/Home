#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include "test_definitions.hpp"

TEST_F(ControllerTest, EmptyInputVectorExpectThrow) {
  ASSERT_THROW(controller->handle({ }), std::exception);
}
TEST_F(ControllerTest, BadInputVectorExpectThrow) {
  ASSERT_THROW(controller->handle({ 'f' }), std::exception);
}
TEST_F(ControllerTest, ReadInputVectorReturnCorrectly) {
  std::stringstream ss { };
  ss << R"(
  {
    "command": "read",
    "files": [
      "1.txt",
      "2.txt",
      "3.txt",
      "4.txt",
      "5.txt"
    ]
  })";
  EXPECT_CALL(boundary, writeFiles).Times(5);
}


#endif
