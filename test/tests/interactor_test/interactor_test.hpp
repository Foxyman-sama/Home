#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include "test_definitions.hpp"

TEST_F(InteractorTest, EmptyInputDataInReadFilesExpectThrow) {
  ASSERT_THROW(interactor->readFiles({ }), std::exception);
}
TEST_F(InteractorTest, EmptyInputDataInWriteFilesExpectThrow) {
  ASSERT_THROW(interactor->writeFiles({ }), std::exception);
}
TEST_F(InteractorTestRead, CorrectCallFunctionRead1000Times) {
  EXPECT_CALL(read_factory, create(AnyOfArray(expected_filenames))).Times(1'000).WillRepeatedly(Return(read_stream));
  EXPECT_CALL(*read_stream, read).Times(1'000).WillRepeatedly(Return(expected_file_data));

  auto output_data { interactor->readFiles({ expected_filenames }) };
  for (auto &&[filename, filedata]: output_data) {
    ASSERT_THAT(filename, AnyOfArray(expected_filenames));
    ASSERT_EQ(filedata, expected_file_data);
  }
}
TEST_F(InteractorTestWrite, CorrectCallFunctionWrite1000Times) {
  EXPECT_CALL(*write_stream, write(expected_file_data)).Times(1'000);
  EXPECT_CALL(write_factory, create(AnyOfArray(expected_filenames))).Times(1'000).WillRepeatedly(Return(write_stream));
  ASSERT_NO_THROW(interactor->writeFiles({ expected_files }));
}

#endif
