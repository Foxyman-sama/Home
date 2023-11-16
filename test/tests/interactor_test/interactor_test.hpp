#ifndef TEST_INTERACTOR_HPP
#define TEST_INTERACTOR_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/business_rules/interactor/interactor.hpp"

using namespace home::entities;
using namespace home::interactor;
using namespace read;
using namespace write;
using namespace testing;

namespace interactor_tests {
class ReadStreamMock
  : public ReadStream {
public:
  MOCK_METHOD(std::vector<char>, read, (), (override));
};
class WriteStreamMock
  : public WriteStream {
public:
  MOCK_METHOD(void, write, (const std::vector<char> &), (override));
};
class ReadStreamFactoryMock 
  : public ReadStreamFactory {
public:
  MOCK_METHOD(std::shared_ptr<ReadStream>, create, (const std::string &), (override));
};
class WriteStreamFactoryMock 
  : public WriteStreamFactory {
public:
  MOCK_METHOD(std::shared_ptr<WriteStream>, create, (const std::string &), (override));
};
class InteractorTest
  : public Test {
protected:
  std::unique_ptr<Interactor> interactor;

  ReadStreamFactoryMock read_factory_mock;
  std::shared_ptr<ReadStreamMock> read_stream_mock;
  WriteStreamFactoryMock write_factory_mock;
  std::shared_ptr<WriteStreamMock> write_stream_mock;

  std::vector<std::string> filenames;
  std::vector<char> filedata;
  Files input_data;
  Files output_data;
  
  void setUpInputDataAndFilenames(size_t index) {
    std::string filename { std::format("{}.txt", index) };
    filenames.emplace_back(filename);
    input_data.emplace_back(std::make_pair(filename, filedata));
  }
  void setUpFactoryMocks(const std::string filename) {
    EXPECT_CALL(write_factory_mock, create(filename)).WillOnce(Return(write_stream_mock));
    EXPECT_CALL(read_factory_mock, create(filename)).WillOnce(Return(read_stream_mock));
  }
  void setUpStreams(size_t files_number) {
    if (files_number > 0) {
      EXPECT_CALL(*write_stream_mock, write(filedata)).Times(files_number);
      EXPECT_CALL(*read_stream_mock, read).Times(files_number).WillRepeatedly(Return(filedata));
    }
  }

public:
  void SetUp() override {
    read_stream_mock = std::make_shared<ReadStreamMock>();
    write_stream_mock = std::make_shared<WriteStreamMock>();
  }

  void givenFilesNumberAndFilesSize(size_t files_number, size_t file_size) {
    filedata.resize(file_size, 'f');
    interactor.reset(new Interactor { "", write_factory_mock, read_factory_mock });
    for (size_t i { }; i < files_number; ++i) {
      setUpInputDataAndFilenames(i);
    }
    
    setUpStreams(files_number);
    for (auto &&filename: filenames) {
      setUpFactoryMocks(filename);
    }
  }
  
  void whenFilesAreWritingAndReading() {
    try {
      interactor->writeFiles(input_data);
      output_data = interactor->readFiles(filenames);
    }
    catch (...) { }
  }

  void thenFilesShouldBeSame() {
    ASSERT_EQ(input_data, output_data);
  }
};

TEST_F(InteractorTest, CorrectWriteAndCorrectRead) {
  givenFilesNumberAndFilesSize(100, 1'000);
  whenFilesAreWritingAndReading();
  thenFilesShouldBeSame();
}
TEST_F(InteractorTest, ZeroFilesWriteAndZeroFilesRead) {
  givenFilesNumberAndFilesSize(0, 1'000);
  whenFilesAreWritingAndReading();
  thenFilesShouldBeSame();
}
TEST_F(InteractorTest, EmptyWriteAndEmptyRead) {
  givenFilesNumberAndFilesSize(100, 0);
  whenFilesAreWritingAndReading();
  thenFilesShouldBeSame();
}
}


#endif
