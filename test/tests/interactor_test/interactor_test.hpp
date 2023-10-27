#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include "test_definitions.hpp"

TEST_F(InteractorTest, EmptyInputDataInReadFilesExpectThrow) {
  ASSERT_THROW(interactor->readFiles({ }), std::exception);
}
TEST_F(InteractorTest, EmptyInputDataInWriteFilesExpectThrow) {
  ASSERT_THROW(interactor->writeFiles({ }), std::exception);
}
TEST_F(InteractorTest, BadInputDataInReadFilesExpectThrow) {
  home::interactor::FileVariant test_case { };
  home::interactor::FilenamesVector test_vector { };
  test_vector.emplace_back("");
  test_case.emplace<1>(test_vector);
  ASSERT_THROW(interactor->readFiles({ test_case }), std::exception);
}
TEST_F(InteractorTest, BadInputDataInWriteFilesExpectThrow) {
  home::interactor::FileVariant test_case { };
  home::interactor::FilenameDataMap test_map { };
  test_map[""] = { };
  test_case.emplace<0>(test_map);
  ASSERT_THROW(interactor->writeFiles({ test_case }), std::exception);
}
TEST_F(InteractorTest, CorrectCallFunctionWriteAndCorrectCallFunctionRead1000Files) {
  std::vector<char> expected { 'f' };
  home::interactor::FilenamesVector test_filenames { };
  home::interactor::FilenameDataMap test_map { };
  for (size_t i { }; i < 1'000; ++i) {
    test_filenames.emplace_back(createFilename(i));
  }

  std::shared_ptr<MockReadStream> read_stream { new MockReadStream { } };
  std::shared_ptr<MockWriteStream> write_stream { new MockWriteStream { } };
  for (auto &&filename: test_filenames) {
    test_map[filename] = expected;
  }

  home::interactor::FileVariant test_case { test_map };
  EXPECT_CALL(*write_stream, write(expected)).Times(1'000);
  EXPECT_CALL(*read_stream, read).Times(1'000);
  EXPECT_CALL(write_factory, create(testing::_)).Times(1'000).WillRepeatedly(testing::Return(write_stream));
  EXPECT_CALL(read_factory, create(testing::_)).Times(1'000).WillRepeatedly(testing::Return(read_stream));
  ASSERT_NO_THROW(interactor->writeFiles({ test_case }));
  ASSERT_NO_THROW(interactor->readFiles({ test_filenames }));
}

#endif
