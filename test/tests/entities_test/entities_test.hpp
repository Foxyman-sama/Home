#ifndef TEST_ENTITIES_HPP
#define TEST_ENTITIES_HPP

#include <gtest/gtest.h>
#include <string_view>
#include <filesystem>
#include "modules/business_rules/entities/entities.hpp"

using namespace home::entities;
using namespace read;
using namespace write;
using namespace testing;

namespace write_stream_create_tests { 
class FileWriteStreamCreate
  : public Test {
protected:
  std::string filename;
  bool is_exception_thrown;
  bool is_stream_open;
  FileWriteStreamFactory factory;

public:
  void SetUp() override {
    is_exception_thrown = false;
  }

  virtual void givenFilename(const std::string &filename) {
    this->filename = filename;
  }

  virtual void whenStreamIsCreating() {
    try {
      factory.create(filename);
    }
    catch (const std::exception &) {
      is_exception_thrown = true;
    }
  }
};
class BadFileWriteCreateTest
  : public FileWriteStreamCreate {
public:
  void thenStreamShouldThrowException() {
    ASSERT_TRUE(is_exception_thrown);
  }
};
class CorrectFileWriteCreateTest
  : public FileWriteStreamCreate {
public:
  void thenStreamShouldBeOpen() {
    ASSERT_FALSE(is_exception_thrown);
  }
};

TEST_F(BadFileWriteCreateTest, PassEmptyFilenameExpectThrow) {
  givenFilename("");
  whenStreamIsCreating();
  thenStreamShouldThrowException();
}
TEST_F(BadFileWriteCreateTest, PassBadFilenameExpectThrow) {
  givenFilename("/");
  whenStreamIsCreating();
  thenStreamShouldThrowException();
}
TEST_F(CorrectFileWriteCreateTest, PassCorrectFilenameExpectBeOpen) {
  givenFilename("1.txt");
  whenStreamIsCreating();
  thenStreamShouldBeOpen();
}
}
namespace write_stream_write_tests {
class FileReadStreamCreate
  : public Test {
protected:
  std::string filename;
  bool is_exception_thrown;
  bool is_stream_open;
  FileReadStreamFactory factory;

public:
  void SetUp() override {

    is_exception_thrown = false;
  }

  virtual void givenFilename(const std::string &filename) {
    this->filename = filename;
  }

  virtual void whenStreamIsCreating() {
    try {
      factory.create(filename);

    }
    catch (const std::exception &) {
      is_exception_thrown = true;
    }
  }
};
class BadFileReadCreateTest
  : public FileReadStreamCreate {
public:
  void thenStreamShouldThrowException() {
    ASSERT_TRUE(is_exception_thrown);
  }
};
class CorrectFileReadCreateTest
  : public FileReadStreamCreate {
public:
  void thenStreamShouldBeOpen() {
    ASSERT_FALSE(is_exception_thrown);
  }
};

TEST_F(BadFileReadCreateTest, PassEmptyFilenameExpectThrow) {
  givenFilename("");
  whenStreamIsCreating();
  thenStreamShouldThrowException();
}
TEST_F(BadFileReadCreateTest, PassBadFilenameExpectThrow) {
  givenFilename("/");
  whenStreamIsCreating();
  thenStreamShouldThrowException();
}
TEST_F(CorrectFileReadCreateTest, PassCorrectFilenameExpectBeOpen) {
  givenFilename("1.txt");
  whenStreamIsCreating();
  thenStreamShouldBeOpen();
}
}

#endif
