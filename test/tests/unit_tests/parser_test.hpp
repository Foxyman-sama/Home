#ifndef TEST_PARSER_HPP
#define TEST_PARSER_HPP

#include "test_base.hpp"
#include "utility/reader.hpp"

class ParserTest : public Test {
 private:
  HTMLParser parser;
  std::vector<std::string> htmls;
  std::unordered_map<std::string, std::string> expected;
  std::unordered_map<std::string, std::string> actual;

 public:
  void appendHTMLs(std::vector<std::string> range) {
    for_each(range, [this](const auto &filename) { htmls.emplace_back(readFile(directory + filename)); });
  }
  void appendExpected(std::vector<std::string> range) {
    for_each(range, [this](const auto &filename) { expected.emplace(filename, readFile(directory + filename)); });
  }

  void parse() {
    for_each(htmls, [this](const auto &html) {
      const auto parsed { parser.parse(html) };
      actual.insert(begin(parsed), end(parsed));
    });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(ParserTest, Parsing_html_with_chrome_boundary) {
  appendHTMLs({ "test_chrome.html" });
  appendExpected({ "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });

  parse();

  assertActualIsEqualExpected();
}
TEST_F(ParserTest, Parsing_html_with_firefox_boundary) {
  appendHTMLs({ "test_firefox.html" });
  appendExpected({ "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });

  parse();

  assertActualIsEqualExpected();
}

#endif