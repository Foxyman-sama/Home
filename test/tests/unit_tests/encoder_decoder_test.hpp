#ifndef TEST_ENCODER_HPP
#define TEST_ENCODER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace controller;

std::array<char, 64> constexpr encode_table { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
std::array<std::uint8_t, 256> constexpr decode_table {
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x3E, 0x64, 0x64, 0x64, 0x3F, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
  0x3D, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
  0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
  0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64
};

class Encoder {
 public:
  std::vector<char> encode(const std::vector<char> &data) {
    const auto size { data.size() };
    const auto full_tripplets { size / 3 };
    std::vector<char> result;
    result.reserve((full_tripplets + 2) * 4);
    for (auto i { 0 }; i < full_tripplets; ++i) {
      auto pos_triplet_start { std::begin(data) + i * 3 };
      auto pos_triplet_end { pos_triplet_start + 3 };
      std::vector<char> triplet { pos_triplet_start, pos_triplet_end };
      const auto base64_chars { encodeTriplet(triplet[0], triplet[1], triplet[2]) };
      std::copy(std::begin(base64_chars), std::end(base64_chars), std::back_inserter(result));
    }

    if (const auto remaining_chars { size - full_tripplets * 3 }; remaining_chars == 2) {
      std::vector<char> triplet { std::begin(data) + size - 2, std::end(data) };
      const auto base64_chars { encodeTriplet(triplet[0], triplet[1], 0) };
      std::copy_n(std::begin(base64_chars), 3, std::back_inserter(result));
      result.emplace_back('=');
    } else if (remaining_chars == 1) {
      const auto base64_chars { encodeTriplet(data.back(), 0, 0) };
      std::copy_n(std::begin(base64_chars), 2, std::back_inserter(result));
      result.emplace_back('=');
      result.emplace_back('=');
    }

    return result;
  }

 private:
  std::array<char, 4> encodeTriplet(std::uint8_t a, std::uint8_t b, std::uint8_t c) {
    const auto concat_bits { static_cast<std::uint32_t>((a << 16) | (b << 8) | c) };
    const auto b64_char1 { encode_table[concat_bits >> 18 & 63] };
    const auto b64_char2 { encode_table[concat_bits >> 12 & 63] };
    const auto b64_char3 { encode_table[concat_bits >> 6 & 63] };
    const auto b64_char4 { encode_table[concat_bits & 63] };
    return { b64_char1, b64_char2, b64_char3, b64_char4 };
  }
};

class Decoder {
 public:
  std::vector<char> decode(const std::vector<char> &data) {
    const auto padding_pos { std::find(std::begin(data), std::end(data), '=') };
    std::vector<char> unpadded_encoded { std::begin(data), padding_pos };
    const auto full_quadruples { unpadded_encoded.size() / 4 };
    std::vector<char> result;
    result.reserve(((full_quadruples + 2) * 3) / 4);
    for (auto i { 0 }; i < full_quadruples; ++i) {
      std::vector<char> quad { std::begin(unpadded_encoded) + i * 4, (std::begin(unpadded_encoded) + i * 4) + 4 };
      const auto bytes { decodeQuad(quad[0], quad[1], quad[2], quad[3]) };
      std::copy(std::begin(bytes), std::end(bytes), std::back_inserter(result));
    }

    if (std::vector<char> last_quad { std::begin(unpadded_encoded) + full_quadruples * 4, std::end(unpadded_encoded) };
        last_quad.size() == 0) {
      return result;
    } else if ((last_quad.size() == 2) || (last_quad[2] == '=')) {
      const auto bytes { decodeQuad(last_quad[0], last_quad[1], 'A', 'A') };
      result.emplace_back(bytes[0]);
    } else {
      const auto bytes { decodeQuad(last_quad[0], last_quad[1], last_quad[2], 'A') };
      std::copy_n(std::begin(bytes), 2, std::back_inserter(result));
    }

    return result;
  }

 private:
  std::array<std::uint8_t, 3> decodeQuad(char a, char b, char c, char d) {
    const auto concat_bytes { static_cast<std::uint32_t>((decode_table[a] << 18) | (decode_table[b] << 12) |
                                                         (decode_table[c] << 6) | decode_table[d]) };
    const auto byte1 { static_cast<std::uint8_t>(concat_bytes >> 16 & 255) };
    const auto byte2 { static_cast<std::uint8_t>(concat_bytes >> 8 & 255) };
    const auto byte3 { static_cast<std::uint8_t>(concat_bytes & 255) };
    return { byte1, byte2, byte3 };
  }
};

class EncoderDecoderTest : public Test {};

TEST_F(EncoderDecoderTest, test) {
  Encoder encoder;
  Decoder decoder;
  std::vector<char> actual { 'I', 'L' };
  auto encoded { encoder.encode(actual) };
  auto decoded { decoder.decode(encoded) };
  ASSERT_EQ(decoded, actual);
}

TEST_F(EncoderDecoderTest, Encoding_and_decoding_100_files_with_max_size_1000_are_correct) {
  Encoder encoder;
  Decoder decoder;
  auto files { generateFiles(10'000, 10'000) };
  for (auto &&[filename, filedata] : files) {
    auto encoded { encoder.encode(filedata) };
    auto decoded { decoder.decode(encoded) };
    ASSERT_EQ(decoded.size(), filedata.size());
    ASSERT_EQ(decoded, filedata);
  }
}

#endif