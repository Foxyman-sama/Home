#ifndef TEST_ENCODER_HPP
#define TEST_ENCODER_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "utility/generators.hpp"

using namespace testing;
using namespace home;
using namespace controller;

constexpr std::array<char, 64> encode_table { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
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

class Container {
 protected:
  std::vector<char> container;
  size_t data_size;

  virtual void setUp(const std::vector<char> &data) noexcept = 0;

  template <typename T, size_t size>
  void append(const std::array<T, size> &src, size_t amount) {
    std::copy_n(std::begin(src), amount, std::back_inserter(container));
  }

  template <typename T>
  std::vector<T> extract(const std::vector<T> &data, size_t start, size_t amount) {
    const auto pos_of_extracted { std::begin(data) + start };
    return { pos_of_extracted, pos_of_extracted + amount };
  }
};
class Encoder : public Container {
 private:
  static constexpr size_t tripplet_size { 3 };
  size_t number_of_tripplets;

 public:
  std::vector<char> encode(const std::vector<char> &data) {
    try {
      return tryEncode(data);
    } catch (...) {
      throw;
    }
  }

 private:
  std::vector<char> tryEncode(const std::vector<char> &data) {
    setUp(data);
    encodeFullTripplets(data);
    encodeRemainingCharsIfExist(data);
    return container;
  }
  void setUp(const std::vector<char> &data) noexcept override {
    data_size = data.size();
    number_of_tripplets = data_size / 3;
    container.clear();
    container.reserve((number_of_tripplets + 2) * 4);
  }
  void encodeFullTripplets(const std::vector<char> &data) {
    for (auto i { 0 }; i < number_of_tripplets; ++i) {
      encodeTrippletByIndex(data, i);
    }
  }
  void encodeTrippletByIndex(const std::vector<char> &data, int index) {
    const auto current_index { index * tripplet_size };
    const auto tripplet { extract(data, current_index, tripplet_size) };
    const auto encoded { encodeTripplet(tripplet[0], tripplet[1], tripplet[2]) };
    append(encoded, 4);
  }
  std::array<char, 4> encodeTripplet(std::uint8_t a, std::uint8_t b = 0, std::uint8_t c = 0) {
    const auto concat_bits { static_cast<std::uint32_t>((a << 16) | (b << 8) | c) };
    const auto b64_char1 { encode_table[concat_bits >> 18 & 63] };
    const auto b64_char2 { encode_table[concat_bits >> 12 & 63] };
    const auto b64_char3 { encode_table[concat_bits >> 6 & 63] };
    const auto b64_char4 { encode_table[concat_bits & 63] };
    return { b64_char1, b64_char2, b64_char3, b64_char4 };
  }

  void encodeRemainingCharsIfExist(const std::vector<char> &data) {
    const auto remaining_chars { data_size - number_of_tripplets * tripplet_size };
    if (remaining_chars == 2) {
      encodeTwoRemainingChars(data);
    } else if (remaining_chars == 1) {
      encodeOneRemainingChars(data);
    }
  }
  void encodeTwoRemainingChars(const std::vector<char> &data) {
    const auto current_index { data_size - 2 };
    const auto tripplet { extract(data, current_index, 2) };
    const auto encoded { encodeTripplet(tripplet[0], tripplet[1]) };
    append(encoded, 3);
    appendPadding(1);
  }
  void encodeOneRemainingChars(const std::vector<char> &data) {
    const auto current_index { data_size - 1 };
    const auto tripplet { extract(data, current_index, 1) };
    const auto encoded { encodeTripplet(tripplet[0]) };
    append(encoded, 2);
    appendPadding(2);
  }
  void appendPadding(size_t number_of_padding) {
    for (auto i { 0 }; i < number_of_padding; ++i) {
      container.emplace_back('=');
    }
  }
};

class Decoder : public Container {
 private:
  static constexpr size_t quadruple_size { 4 };
  std::vector<char> unpadded_encoded;
  size_t number_of_quadruples;

 public:
  std::vector<char> decode(const std::vector<char> &data) {
    setUp(data);
    for (auto i { 0 }; i < number_of_quadruples; ++i) {
      const auto quadruple { extract(data, i * 4, quadruple_size) };
      const auto bytes { decodeQuad(quadruple[0], quadruple[1], quadruple[2], quadruple[3]) };
      append(bytes, 3);
    }

    std::vector<char> last_quad { std::begin(unpadded_encoded) + number_of_quadruples * 4, std::end(unpadded_encoded) };
    if (last_quad.size() == 0) {
      return container;
    } else if (last_quad.size() == 2) {
      const auto bytes { decodeQuad(last_quad[0], last_quad[1], 'A', 'A') };
      append(bytes, 1);
    } else {
      const auto bytes { decodeQuad(last_quad[0], last_quad[1], last_quad[2], 'A') };
      append(bytes, 2);
    }

    return container;
  }

 private:
  void setUp(const std::vector<char> &data) noexcept override {
    unpadded_encoded = { std::begin(data), std::find(std::begin(data), std::end(data), '=') };
    number_of_quadruples = unpadded_encoded.size() / quadruple_size;
    container.clear();
    container.reserve(((number_of_quadruples + 2) * 3) / quadruple_size);
  }

  std::array<std::uint8_t, 3> decodeQuadruplesByIndex(const std::vector<char> &data, size_t index) {
    const auto current_index { index * quadruple_size };
    const auto quadruple { extract(data, current_index, quadruple_size) };
    const auto bytes { decodeQuad(quadruple[0], quadruple[1], quadruple[2], quadruple[3]) };
    append(bytes, 3);
  }
  std::vector<char> extractQuadruple(const std::vector<char> &data, size_t start, size_t amount) {
    const auto pos_of_quadruple { std::begin(data) + start };
    return { pos_of_quadruple, pos_of_quadruple + amount };
  }

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