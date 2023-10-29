#ifndef ENTITIES_TESTS_DEF_HPP
#define ENTITIES_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include "modules/business_rules/entities/filereadstream.hpp"
#include "modules/business_rules/entities/filewritestream.hpp"
#include "../configtest.hpp"

class TestingReadStream {
public:
  std::unique_ptr<home::entities::FileReadStream> reader;

  void open(const std::string &filename) {
    reader.reset(new home::entities::FileReadStream { filename });
  }
  void close() {
    reader.reset();
  }
  auto operator->() {
    return reader.operator->();
  }
};
class TestingWriteStream {
public:
  std::unique_ptr<home::entities::FileWriteStream> writer;

  void open(const std::string &filename) {
    writer.reset(new home::entities::FileWriteStream { filename });
  }
  void close() {
    writer.reset();
  }
  auto operator->() {
    return writer.operator->();
  }
};
class FileReaderTest
  : public testing::Test {
public:
  TestingReadStream read_stream;
};
class FileWriterTest
  : public testing::Test {
public:
  TestingWriteStream write_stream;
};
class FileWriterReaderTest 
  : public testing::Test {
public:
  TestingWriteStream write_stream;
  TestingReadStream read_stream;
};
#endif
