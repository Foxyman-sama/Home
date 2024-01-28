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
using std::ranges::for_each;

class EncoderDecoderTest : public Test {
 private:
  Base64Encoder encoder;
  Base64Decoder decoder;
  HashTable<std::string, std::string> expected;
  HashTable<std::string, std::string> actual;

 public:
  void givenNumberOfFilesAndMaxSizeOfThem(size_t number_of_files, size_t max_size) {
    expected = generateFiles<std::string, std::string>(number_of_files, max_size);
  }

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