#ifndef WRITE_READ_TEST
#define WRITE_READ_TEST

#include "test_base.hpp"
#include "utility/reader.hpp"

class WriteReadTest : public Test {
 private:
  std::vector<std::string> htmls;
  std::vector<std::string> filenames;
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
  void appendFilenames(std::vector<std::string> range) { filenames.insert(begin(filenames), begin(range), end(range)); }

  void handle() {
    for_each(htmls, [this](const auto &html) { controller.save(html); });
    for_each(filenames, [this](const auto &filename) { actual.emplace_back(interactor.get(filename)); });
    for_each(filenames, [this](const auto &filename) { expected.emplace_back(readFile(directory + filename)); });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(WriteReadTest, System_when_html_with_chrome_boundary_comes) {
  appendHTMLs({ "test_chrome.html" });
  appendFilenames({ "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WriteReadTest, System_when_html_with_firefox_boundary_comes) {
  appendHTMLs({ "test_firefox.html" });
  appendFilenames({ "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });

  handle();

  assertActualIsEqualExpected();
}

#endif