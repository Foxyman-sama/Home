#ifndef TEST_ENCODER_DECODER_HPP
#define TEST_ENCODER_DECODER_HPP

#if 0

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "modules/core/decoder_base64.hpp"
#include "modules/core/encoder_base64.hpp"
#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace crypto;
using std::ranges::for_each;

class EncoderDecoderTest : public Test {
 private:
  Base64Encoder encoder;
  Base64Decoder decoder;
  std::unordered_map<std::string, std::string> expected;
  std::unordered_map<std::string, std::string> actual;

 public:
  void givenNumberOfFilesAndMaxSizeOfThem(size_t number_of_files, size_t max_size) { expected = generateFiles(); }

  void whenEncoderIsEncodingAndThenDecoderIsDecoding() {
    for (auto &&[filename, filedata] : expected) {
      const auto encoded { encoder.encode(filedata) };
      actual.emplace(filename, decoder.decode(encoded));
    }
  }

  void thenActualAndExpectedDataShouldBeEqual() { ASSERT_EQ(actual, expected); }
};

TEST_F(EncoderDecoderTest, Encoding_and_decoding_are_correct) {
  givenNumberOfFilesAndMaxSizeOfThem(100, 1'000);
  whenEncoderIsEncodingAndThenDecoderIsDecoding();
  thenActualAndExpectedDataShouldBeEqual();
}

#endif

#endif