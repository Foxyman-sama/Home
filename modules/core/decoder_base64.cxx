#include "decoder_base64.hpp"

namespace home::crypto {

std::string Base64Decoder::decode(const std::string &str) {
  try {
    return tryDecode(str);
  } catch (...) {
    throw std::runtime_error { "Decoding error." };
  }
}
std::string Base64Decoder::tryDecode(const std::string &str) {
  setUp(str);
  decodeFullQuadruples();
  decodeRemainingCharsIfExist();
  return container;
}
void Base64Decoder::setUp(const std::string &str) noexcept {
  if (str.find('=') != std::string::npos) {
    unpadded_encoded = { str.begin(), str.begin() + str.find('=') };
  } else {
    unpadded_encoded = { str.begin(), str.end() };
  }

  data_size = unpadded_encoded.size();
  number_of_quadruples = unpadded_encoded.size() / quadruple_size;
  container.clear();
  // "*3" is reserved for tripplets and we need to divide into quadruple_size because size will decrease
  container.reserve((number_of_quadruples * 3) / quadruple_size);
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
void Base64Decoder::decodeTwoRemainingChars(const std::string &last_quadruple) {
  const auto bytes { decodeQuad(last_quadruple[0], last_quadruple[1], 'A', 'A') };
  append(bytes, 1);
}
void Base64Decoder::decodeThreeRemainingChars(const std::string &last_quadruple) {
  const auto bytes { decodeQuad(last_quadruple[0], last_quadruple[1], last_quadruple[2], 'A') };
  append(bytes, 2);
}

}  // namespace home::crypto