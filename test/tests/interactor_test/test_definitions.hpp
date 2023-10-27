#ifndef INTERACTOR_TESTS_DEF_HPP
#define INTERACTOR_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/business_rules/interactor/interactor.hpp"
#include "modules/business_rules/entities/readstreamfactory.hpp"
#include "modules/business_rules/entities/writestreamfactory.hpp"
#include "../configtest.hpp"

using namespace home::entities;

class MockReadStream
  : public home::entities::ReadStream {
public:  
  MOCK_METHOD(std::vector<char>, read, (), (override));
};
class MockWriteStream
  : public home::entities::WriteStream {
public:  
  MOCK_METHOD(void, write, (const std::vector<char> &), (override));
};
class MockReadStreamFactory
  : public ReadStreamFactory {
public:  
  MOCK_METHOD(std::shared_ptr<home::entities::ReadStream>, create, (const std::string &), (override));
};
class MockWriteStreamFactory
  : public WriteStreamFactory {
public:
  MOCK_METHOD(std::shared_ptr<home::entities::WriteStream>, create, (const std::string &), (override));
};
class InteractorTest 
  : public testing::Test {
public:
  std::unique_ptr<home::interactor::Interactor> interactor;
  MockWriteStreamFactory write_factory;
  MockReadStreamFactory read_factory;

  void SetUp() override {
    interactor.reset(new home::interactor::Interactor { path_test_directory, write_factory, read_factory });
  }
};

#endif
