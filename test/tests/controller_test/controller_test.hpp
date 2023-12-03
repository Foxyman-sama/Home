#ifndef TEST_CONTROLLER_HPP
#define TEST_CONTROLLER_HPP

#include "modules/adapters/deserializerimpl.hpp"
#include "modules/adapters/serializerimpl.hpp"
#include "modules/adapters/web_write_controller.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

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

  void thenShouldThrowException() {
    ASSERT_EQ(is_threw_exception, true);
  }
  void thenShouldNotThrowException() {
    ASSERT_EQ(is_threw_exception, false);
  }
};

TEST_F(WebWriteControllerTest, BadWebDataExpectThrowException) {
  givenCorrectWebData(false);
  whenWebDataIsProcessing();
  thenShouldThrowException();
}
TEST_F(WebWriteControllerTest, CorrectWebDataNotThrowException) {
  givenCorrectWebData(true);
  whenWebDataIsProcessing();
  thenShouldNotThrowException();
}
}
namespace data_generator {

class BinaryConverter {
public:
  static std::vector<char> serializeData(const std::string &data, size_t size_of_data) {
    std::vector<char> result { };
    result.resize(sizeof(size_of_data) + size_of_data);
    std::memcpy(result.data(), &size_of_data, sizeof(size_of_data));
    std::memcpy(result.data() + sizeof(size_of_data), data.data(), size_of_data);
    return result;
  }
};

class GeneratorBase {
protected:
  using ptree = boost::property_tree::ptree;

  void generateJSON(size_t number_of_files) {
    ptree json;
    ptree array;
    for (size_t i { }; i < number_of_files; ++i) {
      array.push_back(makeJSONArrayElement(std::format("{}.txt", i)));
    }

    json.add_child("files", array);

    std::stringstream ss { };
    boost::property_tree::write_json(ss, json);
    generated_json = ss.str();
  }
  std::pair<const char *, ptree> makeJSONArrayElement(const std::string &filename) {
    ptree array_element { };
    array_element.put("", filename);
    return { "", array_element };
  }

  void generateFiles(size_t number_of_files, size_t size_of_file) {
    Files result { };
    for (size_t i { }; i < number_of_files; ++i) {
      std::vector<char> temp_data { };
      temp_data.resize(size_of_file, 'f');
      result.emplace_back(std::make_pair(std::format("{}.txt", i), temp_data));
    }

    generated_files = result;
  }

  void generateBinaryJSONAndFiles() {
    std::vector<char> result { };
    result.append_range(BinaryConverter::serializeData(generated_json, generated_json.size()));
    for (auto &&[filename, filedata]: generated_files) {
      if (filedata.size() > 0) {
        auto serialized_data { BinaryConverter::serializeData(filedata.data(), filedata.size()) };
        result.append_range(serialized_data);
      }
    }

    generated_binary_data = result;
  }

  std::string generated_json;
  Files generated_files;
  std::vector<char> generated_binary_data;
};

}
namespace deserializer_tests {

struct TestData {
  Files expected_data;
  std::vector<char> serialized_data;
};
class Generator
  : public data_generator::GeneratorBase {
public:
  auto generateExpectedDataAndFiles(size_t number_of_files_in_json, size_t number_of_files, size_t size_of_file) {
    generateJSON(number_of_files_in_json);
    generateFiles(number_of_files, size_of_file);
    generateBinaryJSONAndFiles();
    return TestData { generated_files, generated_binary_data };
  }
};

class DeserializerTests
  : public Test {
protected:
  DeserializerImpl deserializer;

  std::vector<char> serialized_data;
  Files expected_data;
  Files actual_data;
  bool is_threw_exception;

public:
  void givenExpectedAndSerializedData(const TestData &test_data) {
    this->expected_data = test_data.expected_data;
    this->serialized_data = test_data.serialized_data;
    this->is_threw_exception = false;
  }

  void whenSerializedDataIsDeserializing() {
    try {
      actual_data = deserializer.deserialize(serialized_data);
    }
    catch (...) {
      is_threw_exception = true;
    }
  }

  void thenActualShouldBeEqualExpectedFiles() {
    ASSERT_EQ(actual_data, expected_data);
  }
  void thenActualFilesShouldBeEmpty() {
    ASSERT_EQ(actual_data.empty(), true);
  }
  void thenDeserializerShouldThrowException() {
    ASSERT_EQ(is_threw_exception, true);
  }
};

Generator generator;

TEST_F(DeserializerTests, Deserialize_correct_data) {
  givenExpectedAndSerializedData(generator.generateExpectedDataAndFiles(100, 100, 100));
  whenSerializedDataIsDeserializing();
  thenActualShouldBeEqualExpectedFiles();
}
TEST_F(DeserializerTests, Deserialize_data_with_empty_json_works_correctly) {
  givenExpectedAndSerializedData(generator.generateExpectedDataAndFiles(0, 100, 100));
  whenSerializedDataIsDeserializing();
  thenActualFilesShouldBeEmpty();
}
TEST_F(DeserializerTests, Deserialize_data_with_empty_files_throw_exception) {
  givenExpectedAndSerializedData(generator.generateExpectedDataAndFiles(100, 100, 0));
  whenSerializedDataIsDeserializing();
  thenDeserializerShouldThrowException();
}
TEST_F(DeserializerTests, Deserialize_empty_data_throw_exception) {
  givenExpectedAndSerializedData(generator.generateExpectedDataAndFiles(0, 0, 0));
  whenSerializedDataIsDeserializing();
  thenDeserializerShouldThrowException();
}

}
namespace serializer_tests {

struct TestData {
  std::vector<char> expected_data;
  Files deserialized_data;
};

class Generator
  : public data_generator::GeneratorBase {
public:
  auto generateExpectedDataAndFiles(size_t number_of_files_in_json, size_t number_of_files, size_t size_of_file) {
    generateJSON(number_of_files_in_json);
    generateFiles(number_of_files, size_of_file);
    generateBinaryJSONAndFiles();
    return TestData { generated_binary_data, generated_files };
  }
};

class SerializerTests
  : public Test {
private:
  SerializerImpl serializer;

  Files deserialized_data;
  std::vector<char> expected_data;
  std::vector<char> actual_data;
  bool is_threw_exception;

public:
  void givenExpectedAndDeserializedData(const TestData &test_data) {
    this->expected_data = test_data.expected_data;
    this->deserialized_data = test_data.deserialized_data;
    this->is_threw_exception = false;
  }

  void whenDeserializedDataIsSerializing() {
    try {
      actual_data = serializer.serialize(deserialized_data);
    }
    catch (const std::exception &) {
      is_threw_exception = true;
    }
  }

  void thenActualShouldBeEqualExpectedData() {
    ASSERT_EQ(actual_data, expected_data);
  }
  void thenActualShouldBeNotEqualExpectedData() {
    ASSERT_NE(actual_data, expected_data);
  }
};

Generator generator;

TEST_F(SerializerTests, Serialize_correct_files) {
  givenExpectedAndDeserializedData(generator.generateExpectedDataAndFiles(100, 100, 100));
  whenDeserializedDataIsSerializing();
  thenActualShouldBeEqualExpectedData();
}
TEST_F(SerializerTests, Serialize_empty_everything_works_correctly) {
  givenExpectedAndDeserializedData(generator.generateExpectedDataAndFiles(0, 0, 0));
  whenDeserializedDataIsSerializing();
  thenActualShouldBeEqualExpectedData();
}
TEST_F(SerializerTests, Serialize_empty_files_works_correctly) {
  givenExpectedAndDeserializedData(generator.generateExpectedDataAndFiles(100, 100, 0));
  whenDeserializedDataIsSerializing();
  thenActualShouldBeEqualExpectedData();
}

}

#endif
