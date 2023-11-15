#ifndef TEST_ENTITIES_HPP
#define TEST_ENTITIES_HPP

#include <gtest/gtest.h>
#include "modules/business_rules/entities/entities.hpp"

using namespace home::entities;
using namespace read;
using namespace write;
using namespace testing;

namespace write_stream_create_tests {
  class FileWriteStreamCreateTest
    : public Test {
  protected:
    std::string filename;
    bool is_exception_thrown;
    FileWriteStreamFactory factory;

  public:
    void SetUp() override {
      is_exception_thrown = false;
    }

    virtual void givenFilenameAndFileSize(const std::string &filename) {
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

    void thenStreamShouldThrowException() {
      ASSERT_TRUE(is_exception_thrown);
    }
    void thenStreamShouldBeOpen() {
      ASSERT_FALSE(is_exception_thrown);
    }
  };

  TEST_F(FileWriteStreamCreateTest, PassEmptyFilenameExpectThrow) {
    givenFilenameAndFileSize("");
    whenStreamIsCreating();
    thenStreamShouldThrowException();
  }
  TEST_F(FileWriteStreamCreateTest, PassBadFilenameExpectThrow) {
    givenFilenameAndFileSize("/");
    whenStreamIsCreating();
    thenStreamShouldThrowException();
  }
  TEST_F(FileWriteStreamCreateTest, PassCorrectFilenameExpectBeOpen) {
    givenFilenameAndFileSize("1.txt");
    whenStreamIsCreating();
    thenStreamShouldBeOpen();
  }
}
namespace read_stream_create_tests {
  class FileReadStreamCreateTest
    : public Test {
  protected:
    std::string filename;
    bool is_exception_thrown;
    FileReadStreamFactory factory;

  public:
    void SetUp() override {
      is_exception_thrown = false;
    }

    virtual void givenFilenameAndFileSize(const std::string &filename) {
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

    void thenStreamShouldThrowException() {
      ASSERT_TRUE(is_exception_thrown);
    }
    void thenStreamShouldBeOpen() {
      ASSERT_FALSE(is_exception_thrown);
    }
  };

  TEST_F(FileReadStreamCreateTest, PassEmptyFilenameExpectThrow) {
    givenFilenameAndFileSize("");
    whenStreamIsCreating();
    thenStreamShouldThrowException();
  }
  TEST_F(FileReadStreamCreateTest, PassBadFilenameExpectThrow) {
    givenFilenameAndFileSize("/");
    whenStreamIsCreating();
    thenStreamShouldThrowException();
  }
  TEST_F(FileReadStreamCreateTest, PassCorrectFilenameExpectBeOpen) {
    givenFilenameAndFileSize("1.txt");
    whenStreamIsCreating();
    thenStreamShouldBeOpen();
  }
}
namespace write_read_process_tests {
  class WriteAndReadTest
    : public Test {
  private:
    FileWriteStreamFactory write_factory;
    FileReadStreamFactory read_factory;
    std::string filename;
    std::vector<char> input_data;
    std::vector<char> output_data;

  public:
    void givenFilenameAndFileSize(const std::string &filename, size_t filesize) {
      this->filename = filename;
      input_data.resize(filesize, 'f');
    }

    void whenStreamsAreWritingAndReading() {
      try {
        write_factory.create(filename)->write(input_data);
        output_data = read_factory.create(filename)->read();
      }
      catch (...) { }
    }

    void thenFileShouldContainSameData() {
      ASSERT_EQ(input_data, output_data);
    }
  };

  TEST_F(WriteAndReadTest, CorrectWriteAndCorrectRead) {
    givenFilenameAndFileSize("1.txt", 1'000);
    whenStreamsAreWritingAndReading();
    thenFileShouldContainSameData();
  }
}

#endif