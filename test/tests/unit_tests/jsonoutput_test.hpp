#ifndef TEST_JSONOUTPUT_HPP
#define TEST_JSONOUTPUT_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <memory>
#include <vector>

using namespace testing;
using namespace home;

class JSONContainer {
 private:
  std::string_view path;
  boost::property_tree::ptree root;

 protected:
  JSONContainer() {}

 public:
  void write(const std::string &filename, const std::vector<char> &filedata) {
    std::string temp;
    std::copy(std::begin(filedata), std::end(filedata), std::back_inserter(temp));
    root.put(filename, temp);
  }

  std::vector<char> read(const std::string &filename) {
    auto file { root.get<std::string>(filename) };
    std::vector<char> result;
    std::copy(std::begin(file), std::end(file), std::back_inserter(result));
    return result;
  }
};

class JSONContainerTest : public Test, private JSONContainer {
 private:
  std::vector<std::string_view> filenames;
  std::vector<std::vector<char>> expected;
  std::vector<std::vector<char>> actual;

 public:
  void givenFilenamesAndData(const std::vector<std::string_view> &filenames,
                             const std::vector<std::string_view> &data) {
    assert(filenames.size() == data.size() && "The sizes are different.");
    this->filenames = filenames;
    for (auto &&filedata : data) {
      expected.emplace_back();
      std::copy(std::begin(filedata), std::end(filedata), std::back_inserter(expected.back()));
    }
  }

  void whenJSONContainerIsWriting() {
    try {
      auto i { filenames.begin() };
      auto j { expected.begin() };
      auto isEnd { [&]() { return (i == filenames.end()) || (j == expected.end()); } };
      for (; isEnd() == false; ++i, ++j) {
        write(i->data(), *j);
      }
    } catch (...) {
    }
  }
  void whenJSONContainerIsReading() {
    try {
      auto i { filenames.begin() };
      auto isEnd { [&]() { return i == filenames.end(); } };
      for (; isEnd() == false; ++i) {
        actual.emplace_back(read(i->data()));
      }
    } catch (...) {
    }
  }

  void thenActualAndExpectedDataShouldBeEqual() { ASSERT_EQ(actual, expected); }
  void thenActualAndExpectedDataShouldBe() { ASSERT_EQ(actual, expected); }
};

TEST_F(JSONContainerTest, JSONContainer_write_and_read_one_char) {
  givenFilenamesAndData({ "1" }, { "1" });
  whenJSONContainerIsWriting();
  whenJSONContainerIsReading();
  thenActualAndExpectedDataShouldBeEqual();
}
TEST_F(JSONContainerTest, JSONContainer_write_and_read_five_words) {
  givenFilenamesAndData({ "1", "2", "3", "4", "5" }, { "Hello", "my", "beautiful", "world", "..." });
  whenJSONContainerIsWriting();
  whenJSONContainerIsReading();
  thenActualAndExpectedDataShouldBeEqual();
}

#endif