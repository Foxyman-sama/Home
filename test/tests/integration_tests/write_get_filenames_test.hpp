#ifndef WRITE_GET_FILENAMES_HPP
#define WRITE_GET_FILENAMES_HPP

#include "test_base.hpp"
#include "utility/reader.hpp"

class WriteGetTest : public Test {
 private:
  std::vector<std::string> htmls;
  std::vector<std::string> actual;
  std::vector<std::string> expected;
  HTMLParser parser;
  JSONContainer container;
  InteractorImpl interactor { container };
  ControllerImpl controller { interactor, parser };

 public:
  void appendHTMLs(std::vector<std::string> range) {
    for_each(range, [this](const auto &filename) {
      const auto filepath { directory + filename };
      htmls.emplace_back(readFile(filepath));
    });
  }
  void appendExpected(std::vector<std::string> range) { expected.insert(begin(expected), begin(range), end(range)); }

  void handle() {
    for_each(htmls, [this](const auto &html) { controller.save(html); });
    actual = controller.getSavedFilenames();
    std::ranges::sort(actual);
    std::ranges::sort(expected);
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(WriteGetTest, System_when_html_with_chrome_boundary_comes) {
  appendHTMLs({ "test_chrome.html" });
  appendExpected({ "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WriteGetTest, System_when_html_with_firefox_boundary_comes) {
  appendHTMLs({ "test_firefox.html" });
  appendExpected({ "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });

  handle();

  assertActualIsEqualExpected();
}

#endif