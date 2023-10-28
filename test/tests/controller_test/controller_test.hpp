#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include "test_definitions.hpp"

TEST_F(ControllerTest, EmptyInputExpectThrow) {
  ASSERT_THROW(controller->handle({ }), std::exception);
}
TEST_F(ControllerTest, BadInputExpectThrow) {
  ASSERT_THROW(controller->handle({ 'f' }), std::exception);
}
TEST_F(ControllerTest, ReadInputReturnCorrectly) {
  std::vector<char> test_case { };
  int temp { 1 };
  test_case.resize(sizeof(int));
  std::memcpy(test_case.data(), &temp, sizeof(int));

  adapters::JSON expected_json { "read", { "1.txt", "2.txt" } };
  interactor::FilenamesVector expected_filenames { expected_json.filenames };
  TestInputData expected_input_data { expected_filenames };
  EXPECT_CALL(converter, convert).WillOnce(testing::Return(expected_json));
  //EXPECT_CALL(boundary, readFiles(expected_input_data));
  ASSERT_NO_THROW(controller->handle({}));
}
TEST_F(ControllerTest, WriteInputReturnCorrectly) {
  adapters::JSON expected_json { "write", { "1.txt", "2.txt" } };
  interactor::FilenameDataMap expected_files { };
  for (auto &&filename: expected_json.filenames) {
    expected_files[filename] = { };
  }

  TestInputData expected_input_data { expected_files };
  EXPECT_CALL(converter, convert).WillOnce(testing::Return(expected_json));
  EXPECT_CALL(boundary, writeFiles(expected_input_data));
  ASSERT_NO_THROW(controller->handle({ }));
}

#endif
