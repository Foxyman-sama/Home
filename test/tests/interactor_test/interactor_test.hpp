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
class FileReadStreamMock
  : public FileReadStream {
public:
  MOCK_METHOD(std::vector<char>, read, (), (override));
};
class FileWriteStreamMock
  : public FileWriteStream {
public:
  MOCK_METHOD(void, write, (const std::vector<char> &), (override));
};
class FileReadStreamFactoryMock 
  : FileReadStreamFactory {
public:
  MOCK_METHOD(std::shared_ptr<ReadStream>, create, (const std::string &), (override));
};
class FileWriteStreamFactoryMock 
  : FileWriteStreamFactory {
public:
  MOCK_METHOD(std::shared_ptr<WriteStream>, create, (const std::string &), (override));
};

class InteractorTest
  : public Test {
public:

};

}


#endif
