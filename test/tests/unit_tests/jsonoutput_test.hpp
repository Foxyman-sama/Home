#ifndef TEST_JSONOUTPUT_HPP
#define TEST_JSONOUTPUT_HPP

#include "test_base.hpp"

namespace {

class JSONContainerWriteAndReadTest : public Test {
 private:
  JSONContainer container;
  std::vector<std::pair<std::string, std::string>> expected;
  std::vector<std::pair<std::string, std::string>> actual;

 public:
  void appendExpected(std::vector<std::pair<std::string, std::string>> range) {
    expected.insert(end(expected), begin(range), end(range));
  }

  void write() {
    for_each(expected, [this](const auto &pair) { container.write(pair.first, pair.second); });
  }
  void read() {
    for_each(expected, [this](const auto &pair) { actual.emplace_back(pair.first, container.read(pair.first)); });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(JSONContainerWriteAndReadTest, Writing_and_reading_empty) {
  appendExpected({});

  write();
  read();

  assertActualIsEqualExpected();
}
TEST_F(JSONContainerWriteAndReadTest, Writing_and_reading_lorem_ipsum) {
  appendExpected(
      { { "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur molestie commodo fringilla. Mauris "
          "fermentum dui vel sapien elementum, quis dictum neque viverra. Suspendisse feugiat nisi id volutpat "
          "imperdiet. Donec est odio, pellentesque eu condimentum vel, rhoncus vitae leo. Aenean dictum consectetur "
          "ante, sit amet convallis urna auctor molestie. Mauris ut egestas lectus, eget ornare nunc. Duis et ligula "
          "vel "
          "justo molestie dignissim vel fermentum purus. Praesent scelerisque molestie lacinia. Sed tristique, sapien "
          "sit amet bibendum bibendum, arcu ipsum volutpat sapien, id tincidunt quam ipsum sed massa. Nam cursus "
          "rutrum "
          "ultrices. ",
          "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur molestie commodo fringilla. Mauris "
          "fermentum dui vel sapien elementum, quis dictum neque viverra. Suspendisse feugiat nisi id volutpat "
          "imperdiet. Donec est odio, pellentesque eu condimentum vel, rhoncus vitae leo. Aenean dictum consectetur "
          "ante, sit amet convallis urna auctor molestie. Mauris ut egestas lectus, eget ornare nunc. Duis et ligula "
          "vel "
          "justo molestie dignissim vel fermentum purus. Praesent scelerisque molestie lacinia. Sed tristique, sapien "
          "sit amet bibendum bibendum, arcu ipsum volutpat sapien, id tincidunt quam ipsum sed massa. Nam cursus "
          "rutrum "
          "ultrices. " } });

  write();
  read();

  assertActualIsEqualExpected();
}

}  // namespace

namespace {

class JSONContainerWriteAndGetFilenamesTest : public Test {
 private:
  JSONContainer container;
  std::vector<std::string> filenames;
  std::vector<std::string> expected;
  std::vector<std::string> actual;

 public:
  void appendExpected(std::vector<std::string> range) { expected.insert(end(expected), begin(range), end(range)); }

  void write() {
    for_each(expected, [this](const auto &filename) { container.write(filename, ""); });
  }
  void getFilenames() { actual = container.getSavedFilenames(); }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(JSONContainerWriteAndGetFilenamesTest, Writing_and_getting_empty) {
  appendExpected({});

  write();
  getFilenames();

  assertActualIsEqualExpected();
}
TEST_F(JSONContainerWriteAndGetFilenamesTest, Writing_and_getting_five_words) {
  appendExpected({ "Hello", "world", "and", "infinity", "space" });

  write();
  getFilenames();

  assertActualIsEqualExpected();
}

}  // namespace
#endif