#ifndef INTERACTOR_TESTS_DEF_HPP
#define INTERACTOR_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/business_rules/interactor/interactor.hpp"
#include "modules/business_rules/entities/entities.hpp"
#include "../entities_test/test_definitions.hpp"

using namespace home::entities;
using namespace write;
using namespace read;
using namespace home::interactor;
using namespace testing;

class MockReadStream
  : public ReadStream {
public:  
  MOCK_METHOD(std::vector<char>, read, (), (override));
};
class MockWriteStream
  : public WriteStream {
public:  
  MOCK_METHOD(void, write, (const std::vector<char> &), (override));
};
class MockReadStreamFactory
  : public ReadStreamFactory {
public:  
  MOCK_METHOD(std::shared_ptr<ReadStream>, create, (const std::string &), (override));
};
class MockWriteStreamFactory
  : public WriteStreamFactory {
public:
  MOCK_METHOD(std::shared_ptr<WriteStream>, create, (const std::string &), (override));
};
class InteractorTest 
  : public Test {
public:
  std::unique_ptr<Interactor> interactor;
  MockWriteStreamFactory write_factory;
  MockReadStreamFactory read_factory;
  std::vector<char> expected_file_data { };
  std::vector<std::string> expected_filenames { };

  void SetUp() override {
    expected_file_data.resize(100'000, 'f');
    for (size_t i { }; i < 1'000; ++i) {
      expected_filenames.emplace_back(TestDirectory::createFilename(i));
    }

    TestDirectory::create();
    interactor.reset(new Interactor { TestDirectory::path_test_directory_files, write_factory, read_factory });
  }
  void TearDown() override {
    TestDirectory::clear();
  }
};
class InteractorTestRead
  : public InteractorTest {
public:
  std::shared_ptr<MockReadStream> read_stream;

  void SetUp() override {
    InteractorTest::SetUp();
    read_stream.reset(new MockReadStream { });
  }
  void TearDown() override {
    InteractorTest::TearDown();
  }
};
class InteractorTestWrite
  : public InteractorTest {
public:
  std::vector<std::string> expected_filenames { };
  std::vector<std::pair<std::string, std::vector<char>>> expected_files { };
  std::shared_ptr<MockWriteStream> write_stream;

  void SetUp() override {
    InteractorTest::SetUp();
    write_stream.reset(new MockWriteStream { });
    for (size_t i { }; i < 1'000; ++i) {
      expected_filenames.emplace_back(TestDirectory::createFilename(i));
    }
    for (auto &&filename: expected_filenames) {
      expected_files.emplace_back(std::make_pair(filename, expected_file_data));
    }
  }
  void TearDown() override {
    InteractorTest::TearDown();
  }
};

#endif
