#ifndef TEST_ENTITIES_HPP
#define TEST_ENTITIES_HPP

#include "test_definitions.hpp"

TEST_F(FileReaderTest, OpenWithEmptyFilenameExpectThrow) {
  ASSERT_THROW(read_stream.open(""), std::exception);
}
TEST_F(FileReaderTest, OpenWithBadFilenameExpectThrow) {
  ASSERT_THROW(read_stream.open("ffff//"), std::exception);
}
TEST_F(FileWriterTest, OpenWithEmptyFilenameExpectThrow) {
  ASSERT_THROW(write_stream.open(""), std::exception);
}
TEST_F(FileWriterTest, OpenWithBadFilenameExpectThrow) {
  ASSERT_THROW(write_stream.open("ffff//"), std::exception);
}
TEST_F(FileWriterReaderTest, WriteAndRead1000TimesWithoutExceptions) {
  for (auto &&file_path: expected_file_paths) {
    ASSERT_NO_THROW(write_stream.open(file_path));
    ASSERT_NO_THROW(write_stream->write(expected_file_data));
    ASSERT_NO_THROW(write_stream.close());
  }
  for (auto &&file_path: expected_file_paths) {
    ASSERT_NO_THROW(read_stream.open(file_path));

    auto actual { read_stream->read() };
    ASSERT_EQ(actual, expected_file_data);
    ASSERT_NO_THROW(read_stream.close());
  }
}

#endif
