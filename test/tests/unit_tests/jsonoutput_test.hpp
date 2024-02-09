#ifndef TEST_JSONOUTPUT_HPP
#define TEST_JSONOUTPUT_HPP

#include "test_base.hpp"

class JSONContainerTest : public Test {
 private:
  JSONContainer container;
  std::vector<std::string> filenames;
  std::vector<std::string> data;
  std::vector<std::pair<std::string, std::string>> expected;
  std::vector<std::pair<std::string, std::string>> actual;

 public:
  void appendFilenames(std::vector<std::string> range) { filenames.insert(end(filenames), begin(range), end(range)); }
  void appendData(std::vector<std::string> range) { data.insert(end(data), begin(range), end(range)); }
  void combine() {
    for_each(zip(filenames, data), [this](const auto &pair) { expected.emplace_back(pair); });
  }
  void write() {
    for_each(expected, [this](const auto &pair) { container.write(pair.first, pair.second); });
  }
  void read() {
    for_each(filenames, [this](const auto &filename) {
      const auto data { container.read(filename) };
      actual.emplace_back(filename, data);
    });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(JSONContainerTest, Writing_and_reading_empty) {
  appendFilenames({});
  appendData({});
  combine();

  write();
  read();

  assertActualIsEqualExpected();
}
TEST_F(JSONContainerTest, Writing_and_reading_lorem_ipsum) {
  appendFilenames(
      { "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur molestie commodo fringilla. Mauris "
        "fermentum dui vel sapien elementum, quis dictum neque viverra. Suspendisse feugiat nisi id volutpat "
        "imperdiet. Donec est odio, pellentesque eu condimentum vel, rhoncus vitae leo. Aenean dictum consectetur "
        "ante, sit amet convallis urna auctor molestie. Mauris ut egestas lectus, eget ornare nunc. Duis et ligula vel "
        "justo molestie dignissim vel fermentum purus. Praesent scelerisque molestie lacinia. Sed tristique, sapien "
        "sit amet bibendum bibendum, arcu ipsum volutpat sapien, id tincidunt quam ipsum sed massa. Nam cursus rutrum "
        "ultrices. " });
  appendData(
      { "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur molestie commodo fringilla. Mauris "
        "fermentum dui vel sapien elementum, quis dictum neque viverra. Suspendisse feugiat nisi id volutpat "
        "imperdiet. Donec est odio, pellentesque eu condimentum vel, rhoncus vitae leo. Aenean dictum consectetur "
        "ante, sit amet convallis urna auctor molestie. Mauris ut egestas lectus, eget ornare nunc. Duis et ligula vel "
        "justo molestie dignissim vel fermentum purus. Praesent scelerisque molestie lacinia. Sed tristique, sapien "
        "sit amet bibendum bibendum, arcu ipsum volutpat sapien, id tincidunt quam ipsum sed massa. Nam cursus rutrum "
        "ultrices. " });
  combine();

  write();
  read();

  assertActualIsEqualExpected();
}

#endif