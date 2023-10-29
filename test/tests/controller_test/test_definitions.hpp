#ifndef CONTROLLER_TESTS_DEF_HPP
#define CONTROLLER_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*

using namespace home;

class MockBoundary
  : public interactor::Boundary {
public:
  MOCK_METHOD(void, writeFiles, (const interactor::InputData &), (override));
  MOCK_METHOD(interactor::OutputData, readFiles, (const interactor::InputData &), (override));
};                                                                                             
class MockJSONConverter
  : public adapters::JSONConverter {
public:
  MOCK_METHOD(adapters::JSON, convert, (const std::vector<char> &), (override));
};                                                                                          
class MockSerializer
  : public adapters::Serializer {
public:
  MOCK_METHOD(std::vector<char>, serialize, (const std::vector<std::vector<char>> &), (override));
};                                                                                          
class MockDeserializer
  : public adapters::Deserializer {
public:  
  MOCK_METHOD(std::vector<std::vector<char>>, deserialize, (const std::vector<char> &), (override));

};
class ControllerTest 
  : public testing::Test {
public:
  std::unique_ptr<adapters::WebController> controller;
  MockBoundary boundary;
  MockJSONConverter converter;
  MockSerializer serializer;
  MockDeserializer deserializer;

  void SetUp() override {
    controller.reset(new adapters::WebController { boundary, converter, serializer, deserializer });
  }
};*/

#endif
