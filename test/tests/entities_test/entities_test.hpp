#ifndef TEST_ENTITIES_HPP
#define TEST_ENTITIES_HPP

#include "test_definitions.hpp"

TEST_F(FileReaderTest, EmptyFilenameExpectThrow) {
  ASSERT_THROW(read_stream.open(""), std::exception);
}
TEST_F(FileReaderTest, BadFilenameExpectThrow) {
  ASSERT_THROW(read_stream.open("ffff//"), std::exception);
}
TEST_F(FileWriterTest, EmptyFilenameExpectThrow) {
  ASSERT_THROW(write_stream.open(""), std::exception);
}
TEST_F(FileWriterTest, BadFilenameExpectThrow) {
  ASSERT_THROW(write_stream.open("ffff//"), std::exception);
}
TEST_F(FileWriterReaderTest, CorrectWriteAndCorrectRead1000Times) {
  recreateTestDirectory();

  std::vector<char> expected { };
  expected.resize(test_file_size, 'f');

  std::vector<std::string> native_filenames_paths { };
  for (size_t i { }; i < 1'000; ++i) {
    std::string native_filename_path { createFilename(i) };
    native_filenames_paths.emplace_back(native_filename_path);
    ASSERT_NO_THROW(write_stream.open(native_filename_path));
    ASSERT_NO_THROW(write_stream->write(expected));
  }

  write_stream.close();

  auto begin { native_filenames_paths.cbegin() };
  auto end { native_filenames_paths.cend() };
  for (auto it { begin }; it != end; ++it) {
    ASSERT_NO_THROW(read_stream.open(*it));
    
    auto actual { read_stream->read() };
    ASSERT_EQ(actual, expected) << "actual_size: " << actual.size();
  }
}

#endif
