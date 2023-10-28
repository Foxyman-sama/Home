#ifndef CONTROLLER_TESTS_DEF_HPP
#define CONTROLLER_TESTS_DEF_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/adapters/webcontroller.hpp"
#include "modules/business_rules/interactor/boundary.hpp"
#include "../configtest.hpp"

using namespace home;

class TestInputData 
  : public interactor::InputData {
public:
  bool operator==(const TestInputData &another) const noexcept {
    if (this->files == another.files) {
      return false;
    }

    return true;
  }
};
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

class ControllerTest 
  : public testing::Test {
public:
  std::unique_ptr<adapters::WebController> controller;
  MockBoundary boundary;
  MockJSONConverter converter;

  void SetUp() override {
    controller.reset(new adapters::WebController { boundary, converter });
  }
};

#endif
