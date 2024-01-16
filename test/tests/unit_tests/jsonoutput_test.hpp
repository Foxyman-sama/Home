#ifndef TEST_JSONOUTPUT_HPP
#define TEST_JSONOUTPUT_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "modules/core/json_container.hpp"

using namespace testing;
using namespace home;
using namespace interactor;
using namespace container;
using std::ranges::for_each;
using std::ranges::views::zip;

class JSONContainerTest : public Test, private JSONContainer {
 private:
  std::vector<std::string> filenames;
  std::vector<std::string> expected;
  std::vector<std::string> actual;

 public:
  void givenFilenamesAndData(const std::vector<std::string> &filenames, const std::vector<std::string> &data) {
    assert(filenames.size() == data.size() && "The sizes are different.");
    this->filenames = filenames;
    this->expected = data;
  }

  void whenJSONContainerIsWriting() {
    auto zipped { zip(filenames, expected) };
    for_each(zipped, [this](auto &&tuple) { write(std::get<0>(tuple), std::get<1>(tuple)); });
  }
  void whenJSONContainerIsReading() {
    for_each(filenames, [&](auto &&filename) { actual.emplace_back(read(filename)); });
  }

  void thenActualAndExpectedDataShouldBeEqual() { ASSERT_EQ(actual, expected); }
};

TEST_F(JSONContainerTest, JSONContainer_write_and_read_empty) {
  givenFilenamesAndData({}, {});
  whenJSONContainerIsWriting();
  whenJSONContainerIsReading();
  thenActualAndExpectedDataShouldBeEqual();
}
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