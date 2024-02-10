#ifndef GENERAL_TEST
#define GENERAL_TEST

#include "test_base.hpp"
#include "utility/reader.hpp"

class Gtest : public Test {
 private:
  std::vector<std::string> htmls;
  size_t expected_number_of_files;
  size_t expected_size_of_files;
  HTMLParser parser;
  JSONContainer container { "build/test.json" };
  InteractorImpl interactor { container };
  ControllerImpl controller { interactor, parser };

 public:
  void appendHTMLs(std::vector<std::string> range) {
    for_each(range, [this](const auto &path) { htmls.emplace_back(readFile(path)); });
  }
};

#if 0

TEST_F(GeneralTest, saveFiles_and_getFile_files) {
  GTEST_SKIP();

  HTMLParser parser;
  JSONContainer container { "build/test.json" };
  InteractorImpl interactor { container };
  ControllerImpl controller { interactor, parser };

  auto returned_info { controller.save(expected_data) };
  auto number_of_files_in_returned_info { std::stoi(returned_info.at(title_number_of_files.data())) };
  auto amount_of_data_in_returned_info { std::stoi(returned_info.at(title_amount_of_data.data())) };
  auto processed_amount_of_data { 0 };
  for (auto &&filename : filenames) {
    processed_amount_of_data += interactor.get(filename).size();
  }

  ASSERT_EQ(number_of_files_in_returned_info, expected_number_of_files)
      << std::format("Number of files: {}; Expected: {}", number_of_files_in_returned_info, expected_number_of_files);
  ASSERT_EQ(amount_of_data_in_returned_info, expected_size_of_files)
      << std::format("Amount of data: {}; Expected: {}", amount_of_data_in_returned_info, expected_size_of_files);
  ASSERT_EQ(processed_amount_of_data, expected_size_of_files) << std::format(
      "Processed amount of data: {}; Expected: {}", amount_of_data_in_returned_info, expected_size_of_files);
}

#endif

#endif