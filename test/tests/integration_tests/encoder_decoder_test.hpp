#ifndef TEST_ENCODER_DECODER_HPP
#define TEST_ENCODER_DECODER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "modules/core/decoder_base64.hpp"
#include "modules/core/encoder_base64.hpp"
#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace crypto;

class EncoderDecoderTest : public Test {
 private:
  Base64Encoder encoder;
  Base64Decoder decoder;
  HashTable<std::string, std::vector<char>> expected;
  HashTable<std::string, std::vector<char>> actual;

 public:
  void givenNumberOfFilesAndMaxSizeOfThem(size_t number_of_files, size_t max_size) {
    expected = generateFiles(number_of_files, max_size);
  }

  void whenEncoderIsEncodingAndDecoderIsDecoding() {
    try {
      for (auto &&[filename, filedata] : expected) {
        auto encoded { encoder.encode(filedata) };
        auto decoded { decoder.decode(encoded) };
      }
    } catch (...) {
    }
  }
};

TEST_F(EncoderDecoderTest, Encoding_and_decoding_100_files_with_max_size_1000_are_correct) {
  Base64Encoder encoder;
  Base64Decoder decoder;
  auto files { generateFiles(100, 1'000) };
  for (auto &&[filename, filedata] : files) {
    auto encoded { encoder.encode(filedata) };
    auto decoded { decoder.decode(encoded) };
    ASSERT_EQ(decoded.size(), filedata.size());
    ASSERT_EQ(decoded, filedata);
  }
}

#endif