#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "modules/adapters/web_write_controller.hpp"

using namespace home::entities;
using namespace home::interactor;
using namespace home::adapters;
using namespace read;
using namespace write;
using namespace testing;

namespace web_write_controller_tests {
  class DeserializerMock
    : public Deserializer {
  public:
    MOCK_METHOD(Files, deserialize, (const std::vector<char> &), (override));
  };
  class WriteBoundaryMock 
    : public WriteBoundary {
  public:
    MOCK_METHOD(void, writeFiles, (const Files &), (override));
  };
  class WebWriteControllerTest
    : public Test {
  protected:
    std::unique_ptr<WebWriteController> controller;

    DeserializerMock deserializer_mock;
    WriteBoundaryMock write_boundary_mock;

    Files test_files;
    bool is_threw_exception;

    Files createTestFiles() {
      return Files { std::pair<std::string, std::vector<char>> { "test", { 'f' } } };
    }

  public:
    void SetUp() override {
      controller.reset(new WebWriteController { write_boundary_mock, deserializer_mock });
      test_files = createTestFiles();
      is_threw_exception = false;
    }

    void givenCorrectWebData(bool is_web_data_correct) {
      if (is_web_data_correct) {
        EXPECT_CALL(deserializer_mock, deserialize).WillOnce(Return(test_files));
        EXPECT_CALL(write_boundary_mock, writeFiles(test_files));
      }
      else {
        EXPECT_CALL(deserializer_mock, deserialize).WillOnce(Throw(std::exception { }));
      }
    }

    void whenWebDataIsProcessing() {
      try {
        controller->write({ });
      }
      catch (const std::exception &) {
        is_threw_exception = true;
      }
    }
  };
  class WebWriteControllerTestWithBadData
    : public WebWriteControllerTest {
  public:
    void thenShouldThrowException() {
      ASSERT_EQ(is_threw_exception, true);
    }
  };
  class WebWriteControllerTestWithCorrectData
    : public WebWriteControllerTest {
  public:
    void thenShouldNotThrowException() {
      ASSERT_EQ(is_threw_exception, false);
    }
  };

  TEST_F(WebWriteControllerTestWithBadData, BadWebDataExpectThrow) {
    givenCorrectWebData(false);
    whenWebDataIsProcessing();
    thenShouldThrowException();
  }
  TEST_F(WebWriteControllerTestWithCorrectData, CorrectWebDataNotThrow) {
    givenCorrectWebData(true);
    whenWebDataIsProcessing();
    thenShouldNotThrowException();
  }
}

#endif
