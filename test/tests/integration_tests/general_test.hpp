#ifndef GENERAL_TEST
#define GENERAL_TEST

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "modules/core/controller_impl.hpp"
#include "modules/core/interactor_impl.hpp"
#include "modules/core/json_container.hpp"
#include "modules/webserver/htmlparser.hpp"
#include "utility/html_maker.hpp"
#include "utility/reader.hpp"

using namespace testing;
using namespace home;
using namespace controller;
using namespace webserver;
using namespace interactor;
using namespace container;
using namespace crypto;

class GeneralTest : public Test {
 private:
  Reader reader;
  HTMLMaker generator;

 public:
  std::string expected_data;
  size_t expected_number_of_files;
  size_t expected_size_of_files;
  std::vector<std::string> filenames;

  void SetUp() override {
    reader.open("build/", "sending_test_input.txt");
    while (reader.isEndOfFile() == false) {
      std::string buffer { reader.readString() };
      if (buffer == "create") {
        createFile(reader);
      } else if (buffer == "append") {
        appendFile(reader);
      }
    }

    auto [data, number_of_files, size_of_files] { generator.getGeneratedParamsAndIfNotEmptyAddLastBounary() };
    expected_data = data;
    expected_number_of_files = number_of_files;
    expected_size_of_files = size_of_files;
    generator.clearGeneratedData();
  }

 private:
  void createFile(Reader &reader) {
    auto filename { reader.readString() };
    filenames.emplace_back(filename);

    auto size { reader.readNumber() };
    auto symbol { reader.readString() };
    expected_size_of_files += size;
    generator.makeTextFileAndAppend(filename, size, symbol);
  }

  void appendFile(Reader &reader) {
    auto filename { reader.readString() };
    filenames.emplace_back(filename);

    auto binary_data { readFile("build/" + filename) };
    expected_size_of_files += binary_data.size();
    generator.appendFile(filename, binary_data);
  }
};

TEST_F(GeneralTest, Save_and_get_files) {
  HTMLParser parser;
  JSONContainer container { "build/test.json" };
  InteractorImpl interactor { container };
  ControllerImpl controller { interactor, parser };

  auto returned_info { controller.save(expected_data) };
  auto number_of_files_in_returned_info { std::stoi(returned_info.at(title_number_of_files.data())) };
  auto amount_of_data_in_returned_info { std::stoi(returned_info.at(title_amount_of_data.data())) };
  auto processed_amount_of_data { 0 };
  for (auto &&filename : filenames) {
    processed_amount_of_data += interactor.decodeAndGet(filename).size();
  }

  ASSERT_EQ(number_of_files_in_returned_info, expected_number_of_files)
      << std::format("Number of files: {}; Expected: {}", number_of_files_in_returned_info, expected_number_of_files);
  ASSERT_EQ(amount_of_data_in_returned_info, expected_size_of_files)
      << std::format("Amount of data: {}; Expected: {}", amount_of_data_in_returned_info, expected_size_of_files);
  ASSERT_EQ(processed_amount_of_data, expected_size_of_files) << std::format(
      "Processed amount of data: {}; Expected: {}", amount_of_data_in_returned_info, expected_size_of_files);
}

#endif