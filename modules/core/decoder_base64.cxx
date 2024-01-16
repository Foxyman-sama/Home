#include "decoder_base64.hpp"

namespace home::crypto {

std::string Base64Decoder::decode(const std::string &str) {
  auto temp { Converter::stringToVector(str) };
  auto result { decode(temp) };
  return Converter::vectorToString(result);
}
std::vector<char> Base64Decoder::decode(const std::vector<char> &data) {
  try {
    return tryDecode(data);
  } catch (...) {
    throw;
  }
}
std::vector<char> Base64Decoder::tryDecode(const std::vector<char> &data) {
  setUp(data);
  decodeFullQuadruples();
  decodeRemainingCharsIfExist();
  return container;
}
void Base64Decoder::setUp(const std::vector<char> &data) noexcept {
  auto last_unpadded_char { std::find(std::begin(data), std::end(data), '=') };
  unpadded_encoded = { std::begin(data), last_unpadded_char };
  data_size = unpadded_encoded.size();
  number_of_quadruples = unpadded_encoded.size() / quadruple_size;
  container.clear();
  container.reserve(((number_of_quadruples + 2) * 3) / quadruple_size);
}

void Base64Decoder::decodeFullQuadruples() {
  for (auto i { 0 }; i < number_of_quadruples; ++i) {
    decodeQuadruplesByIndex(i);
  }
}
void Base64Decoder::decodeQuadruplesByIndex(size_t index) {
  const auto current_index { index * quadruple_size };
  const auto quadruple { extract(unpadded_encoded, current_index, quadruple_size) };
  const auto bytes { decodeQuad(quadruple[0], quadruple[1], quadruple[2], quadruple[3]) };
  append(bytes, 3);
}
std::array<std::uint8_t, 3> Base64Decoder::decodeQuad(char a, char b, char c, char d) {
  const auto concat_bytes { static_cast<std::uint32_t>((decode_table[a] << 18) | (decode_table[b] << 12) |
                                                       (decode_table[c] << 6) | decode_table[d]) };
  const auto byte1 { static_cast<std::uint8_t>(concat_bytes >> 16 & 255) };
  const auto byte2 { static_cast<std::uint8_t>(concat_bytes >> 8 & 255) };
  const auto byte3 { static_cast<std::uint8_t>(concat_bytes & 255) };
  return { byte1, byte2, byte3 };
}

void Base64Decoder::decodeRemainingCharsIfExist() {
  const auto remaining_chars { data_size - number_of_quadruples * quadruple_size };
  const auto last_quadruple { extract(unpadded_encoded, number_of_quadruples * quadruple_size, remaining_chars) };
  if (last_quadruple.size() == 2) {
    decodeTwoRemainingChars(last_quadruple);
  } else if (last_quadruple.size() == 3) {
    decodeThreeRemainingChars(last_quadruple);
  }
}
void Base64Decoder::decodeTwoRemainingChars(const std::vector<char> &last_quadruple) {
  const auto bytes { decodeQuad(last_quadruple[0], last_quadruple[1], 'A', 'A') };
  append(bytes, 1);
}
void Base64Decoder::decodeThreeRemainingChars(const std::vector<char> &last_quadruple) {
  const auto bytes { decodeQuad(last_quadruple[0], last_quadruple[1], last_quadruple[2], 'A') };
  append(bytes, 2);
}

}  // namespace home::crypto

namespace home::test {

std::string Base64DecoderTest::decode(const std::string &str) {
  try {
    return tryDecode(str);
  } catch (...) {
    throw;
  }
}
std::string Base64DecoderTest::tryDecode(const std::string &str) {
  setUp(str);
  decodeFullQuadruples();
  decodeRemainingCharsIfExist();
  return container;
}
void Base64DecoderTest::setUp(const std::string &str) noexcept {
  auto last_unpadded_char { std::find(std::begin(str), std::end(str), '=') };
  unpadded_encoded = { std::begin(str), last_unpadded_char };
  data_size = unpadded_encoded.size();
  number_of_quadruples = unpadded_encoded.size() / quadruple_size;
  container.clear();
  container.reserve(((number_of_quadruples + 2) * 3) / quadruple_size);
}

void Base64DecoderTest::decodeFullQuadruples() {
  for (auto i { 0 }; i < number_of_quadruples; ++i) {
    decodeQuadruplesByIndex(i);
  }
}
void Base64DecoderTest::decodeQuadruplesByIndex(size_t index) {
  const auto current_index { index * quadruple_size };
  const auto quadruple { extract(unpadded_encoded, current_index, quadruple_size) };
  const auto bytes { decodeQuad(quadruple[0], quadruple[1], quadruple[2], quadruple[3]) };
  append(bytes, 3);
}
std::array<std::uint8_t, 3> Base64DecoderTest::decodeQuad(char a, char b, char c, char d) {
  const auto concat_bytes { static_cast<std::uint32_t>((decode_table[a] << 18) | (decode_table[b] << 12) |
                                                       (decode_table[c] << 6) | decode_table[d]) };
  const auto byte1 { static_cast<std::uint8_t>(concat_bytes >> 16 & 255) };
  const auto byte2 { static_cast<std::uint8_t>(concat_bytes >> 8 & 255) };
  const auto byte3 { static_cast<std::uint8_t>(concat_bytes & 255) };
  return { byte1, byte2, byte3 };
}

void Base64DecoderTest::decodeRemainingCharsIfExist() {
  const auto remaining_chars { data_size - number_of_quadruples * quadruple_size };
  const auto last_quadruple { extract(unpadded_encoded, number_of_quadruples * quadruple_size, remaining_chars) };
  if (last_quadruple.size() == 2) {
    decodeTwoRemainingChars(last_quadruple);
  } else if (last_quadruple.size() == 3) {
    decodeThreeRemainingChars(last_quadruple);
  }
}
void Base64DecoderTest::decodeTwoRemainingChars(const std::string &last_quadruple) {
  const auto bytes { decodeQuad(last_quadruple[0], last_quadruple[1], 'A', 'A') };
  append(bytes, 1);
}
void Base64DecoderTest::decodeThreeRemainingChars(const std::string &last_quadruple) {
  const auto bytes { decodeQuad(last_quadruple[0], last_quadruple[1], last_quadruple[2], 'A') };
  append(bytes, 2);
}

}  // namespace home::test