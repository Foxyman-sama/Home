#ifndef TEST_ENCODER_HPP
#define TEST_ENCODER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace controller;

class Encoder {
 private:
  static constexpr std::array<char, 64> encode_table { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                                       'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                                       'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                                       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                                       '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

 public:
  std::vector<char> encode(const std::vector<char> &data) {
    auto processed { 0 };
    auto i { 0 };
    std::vector<char> temp;
    std::vector<char> result;
    while (processed < data.size()) {
      temp.emplace_back(data[processed++]);
      if (++i % 3 == 0) {
        temp = encode_triplet(temp[0], temp[1], temp[2]);
        result.insert(result.end(), { temp[0], temp[1], temp[2], temp[3] });
        temp.clear();
        i = 0;
      }
    }
    while (++i <= 3) {
      result.emplace_back('=');
    }

    return result;
  }

 private:
  std::vector<char> encode_triplet(char a, char b, char c) {
    const std::uint32_t concat_bits { (a << 16) | (b << 8) | c };
    const auto b64_char1 { encode_table[(concat_bits >> 18) & 63] };
    const auto b64_char2 { encode_table[(concat_bits >> 12) & 63] };
    const auto b64_char3 { encode_table[(concat_bits >> 6) & 63] };
    const auto b64_char4 { encode_table[concat_bits & 63] };
    return { b64_char1, b64_char2, b64_char3, b64_char4 };
  }
};

class Decoder {
 private:
  static constexpr std::array<std::uint8_t, 128> decode_table {
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x3E, 0x64, 0x64, 0x64, 0x3F, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
    0x3D, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
    0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
    0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x64, 0x64, 0x64, 0x64, 0x64
  };

 public:
  std::vector<char> decode(const std::vector<char> &data) {
    auto processed { 0 };
    auto i { 0 };
    std::vector<char> temp;
    std::vector<char> result;
    while (processed < data.size()) {
      temp.emplace_back(data[processed++]);
      if (++i % 4 == 0) {
        temp = decode_quad(temp[0], temp[1], temp[2], temp[3]);
        result.insert(result.end(), { temp[0], temp[1], temp[2] });
        temp.clear();
        i = 0;
      }
    }

    return result;
  }

 private:
  std::vector<char> decode_quad(char a, char b, char c, char d) {
    const std::uint32_t concat_bytes { (decode_table[a] << 18) | (decode_table[b] << 12) | (decode_table[c] << 6) |
                                       decode_table[d] };
    const char byte1 { (concat_bytes >> 16) & 255 };
    const char byte2 { (concat_bytes >> 8) & 255 };
    const char byte3 { concat_bytes & 255 };
    return { byte1, byte2, byte3 };
  }
};

class EncoderDecoderTest : public Test {};

TEST_F(EncoderDecoderTest, Encoding_and_decoding_100_files_with_max_size_1000_are_correct) {
  Encoder encoder;
  Decoder decoder;
  auto files { generateFiles(100, 1000) };
  for (auto &&[filename, filedata] : files) {
    auto encoded { encoder.encode(filedata) };
    auto decoded { decoder.decode(encoded) };
    ASSERT_EQ(decoded, filedata);
  }
}

#endif