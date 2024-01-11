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
  boost::property_tree::ptree root;
  boost::property_tree::ptree files;

 public:
  void write(const std::string &filename, const std::vector<char> &filedata) {
    std::string temp;
    std::copy(std::begin(filedata), std::end(filedata), std::back_inserter(temp));
    files.put(filename, temp);
  }
  std::vector<char> read(const std::string &filename) {
    std::string temp { files.get_value(filename) };
    std::vector<char> result;
    std::copy(std::begin(temp), std::end(temp), std::back_inserter(result));
    return result;
  }
};

TEST(JSONContainerTest, Json_output) {
  std::vector<char> expected { '1' };
  JSONContainer container;
  container.write("1", expected);

  auto actual { container.read("1") };
  ASSERT_EQ(expected, actual);
}

#endif