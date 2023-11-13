#ifndef ENTITIES_TESTS_DEF_HPP
#define ENTITIES_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <string_view>
#include <filesystem>
#include "modules/business_rules/entities/entities.hpp"

using namespace home::entities;
using namespace read;
using namespace write;
using namespace testing;

class TestDirectory {
public:
  static inline const std::string path_test_directory_core { "files/" };
  static inline const std::string path_test_directory_files { path_test_directory_core + "test/" };
  static inline const std::string test_filename { "test.txt" };
  
  static void recreate() {
    clear();
    create();
  }
  static void create() {
    std::filesystem::create_directories(path_test_directory_files);
  }
  static void clear() {
    std::filesystem::remove_all(path_test_directory_core);
  }
  static std::string createFilename(size_t index) {
    return path_test_directory_files + std::to_string(index) + test_filename;
  }
};
class TestReadStream {
private:
  std::unique_ptr<FileReadStream> reader;

public:
  void open(const std::string &filename) {
    reader.reset(new FileReadStream { filename });
  }
  void close() {
    reader.reset();
  }
  auto operator->() {
    return reader.operator->();
  }
};
class TestWriteStream {
private:
  std::unique_ptr<FileWriteStream> writer;

public:
  void open(const std::string &filename) {
    writer.reset(new FileWriteStream { filename });
  }
  void close() {
    writer.reset();
  }
  auto operator->() {
    return writer.operator->();
  }
};
class FileReaderTest
  : public Test {
public:
  TestReadStream read_stream;
};
class FileWriterTest
  : public Test {
public:
  TestWriteStream write_stream;
};
class FileWriterReaderTest 
  : public Test {
public:
  TestWriteStream write_stream;
  TestReadStream read_stream;
  std::vector<char> expected_file_data { };
  std::vector<std::string> expected_file_paths { };

  void SetUp() override {
    TestDirectory::create();
    expected_file_data.resize(100'000, 'f');
    for (size_t i { }; i < 1'000; ++i) {
      std::string file_path { TestDirectory::createFilename(i) };
      expected_file_paths.emplace_back(file_path);
    }
  }
  void TearDown() override {
    TestDirectory::clear();
  }
};
#endif
