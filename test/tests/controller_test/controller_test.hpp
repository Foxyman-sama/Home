#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include "test_definitions.hpp"

/*
TEST_F(ControllerTest, EmptyInputExpectThrow) {
  ASSERT_THROW(controller->handle({ }), std::exception);
}
TEST_F(ControllerTest, BadInputExpectThrow) {
  ASSERT_THROW(controller->handle({ 'f' }), std::exception);
}
TEST_F(ControllerTest, ReadInputReturnCorrectly) {
  constexpr std::string_view test_receive_json { R"(
    {
      "command": "read",
      "files": [ 
        "1.txt", "2.txt", "3.txt"]
    })" };
  auto size { test_receive_json.size() };
  std::vector<char> expected_desirializer_arg { };
  std::vector<std::vector<char>> expected_desirializer_return { { } };
  expected_desirializer_arg.resize(sizeof(size));
  expected_desirializer_return[0].resize(size);
  std::memcpy(expected_desirializer_return[0].data(), test_receive_json.data(), size);
  std::memcpy(expected_desirializer_arg.data(), &size, sizeof(size));
  expected_desirializer_arg.append_range(expected_desirializer_return[0]);

  adapters::JSON expected_json { "read", { "1.txt", "2.txt" } };
  interactor::FilenamesVector expected_filenames { expected_json.filenames };
  interactor::InputData expected_input_data { expected_filenames };
  EXPECT_CALL(deserializer, deserialize(expected_desirializer_arg)).WillOnce(testing::Return(expected_desirializer_return));
  EXPECT_CALL(converter, convert(expected_desirializer_return[0])).WillOnce(testing::Return(expected_json));
  EXPECT_CALL(boundary, readFiles); // TODO
  ASSERT_NO_THROW(controller->handle({}));
}
TEST_F(ControllerTest, WriteInputReturnCorrectly) {
  adapters::JSON expected_json { "write", { "1.txt", "2.txt" } };
  interactor::FilenameDataMap expected_files { };
  for (auto &&filename: expected_json.filenames) {
    expected_files[filename] = { };
  }

  interactor::InputData expected_input_data { expected_files };
  EXPECT_CALL(converter, convert).WillOnce(testing::Return(expected_json));
  EXPECT_CALL(boundary, writeFiles); // TODO
  ASSERT_NO_THROW(controller->handle({ }));
}
*/
#endif
