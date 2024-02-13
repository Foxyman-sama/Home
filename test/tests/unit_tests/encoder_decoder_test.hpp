#ifndef TEST_ENCODER_DECODER_HPP
#define TEST_ENCODER_DECODER_HPP

#include "test_base.hpp"
#include "utility/generators.hpp"

class EncoderDecoderTest : public Test {
 private:
  Base64Encoder encoder;
  Base64Decoder decoder;
  std::unordered_map<std::string, std::string> expected;
  std::unordered_map<std::string, std::string> encoded;
  std::unordered_map<std::string, std::string> actual;

 public:
  void appendExpected(std::unordered_map<std::string, std::string> range) { expected.insert(begin(range), end(range)); }

  void encode() {
    for_each(expected, [this](const auto &pair) {
      const auto encoded_filename { encoder.encode(pair.first) };
      const auto encoded_filedata { encoder.encode(pair.second) };
      encoded.emplace(encoded_filename, encoded_filedata);
    });
  }
  void decode() {
    for_each(encoded, [this](const auto &pair) {
      const auto decoded_filename { decoder.decode(pair.first) };
      const auto decoded_filedata { decoder.decode(pair.second) };
      actual.emplace(decoded_filename, decoded_filedata);
    });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(EncoderDecoderTest, Encoding_and_decoding_files) {
  appendExpected(generateFiles());

  encode();
  decode();

  assertActualIsEqualExpected();
}

#endif