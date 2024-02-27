#include "encoder_base64.hpp"

namespace home::crypto {

std::string Base64Encoder::encode(const std::string &str) {
  try {
    return tryEncode(str);
  } catch (...) {
    throw std::runtime_error { "Encoding error." };
  }
}
std::string Base64Encoder::tryEncode(const std::string &str) {
  setUp(str);
  encodeFullTripplets(str);
  encodeRemainingCharsIfExist(str);
  return container;
}
void Base64Encoder::setUp(const std::string &str) noexcept {
  data_size = str.size();
  number_of_tripplets = data_size / 3;
  container.clear();
  // "+2" is reserved for padding and "*4" is reserved for quadruples because we from raw tripplets make encoded
  // quadruples
  container.reserve((number_of_tripplets + 2) * 4);
}
void Base64Encoder::encodeFullTripplets(const std::string &str) {
  for (auto i { 0 }; i < number_of_tripplets; ++i) {
    encodeTrippletByIndex(str, i);
  }
}
void Base64Encoder::encodeTrippletByIndex(const std::string &str, int index) {
  const auto current_index { index * tripplet_size };
  const auto tripplet { extract(str, current_index, tripplet_size) };
  const auto encoded { encodeTripplet(tripplet[0], tripplet[1], tripplet[2]) };
  append(encoded, 4);
}
std::array<char, 4> Base64Encoder::encodeTripplet(std::uint8_t a, std::uint8_t b, std::uint8_t c) {
  const auto concat_bits { static_cast<std::uint32_t>((a << 16) | (b << 8) | c) };
  const auto b64_char1 { encode_table[concat_bits >> 18 & 63] };
  const auto b64_char2 { encode_table[concat_bits >> 12 & 63] };
  const auto b64_char3 { encode_table[concat_bits >> 6 & 63] };
  const auto b64_char4 { encode_table[concat_bits & 63] };
  return { b64_char1, b64_char2, b64_char3, b64_char4 };
}

void Base64Encoder::encodeRemainingCharsIfExist(const std::string &str) {
  // We take the size of the full tripplets and it substracts from the data size
  const auto remaining_chars { data_size - number_of_tripplets * tripplet_size };
  if (remaining_chars == 2) {
    encodeTwoRemainingChars(str);
  } else if (remaining_chars == 1) {
    encodeOneRemainingChar(str);
  }
}
void Base64Encoder::encodeTwoRemainingChars(const std::string &str) {
  const auto current_index { data_size - 2 };
  const auto tripplet { extract(str, current_index, 2) };
  const auto encoded { encodeTripplet(tripplet[0], tripplet[1]) };
  append(encoded, 3);
  appendPadding(1);
}
void Base64Encoder::encodeOneRemainingChar(const std::string &str) {
  const auto current_index { data_size - 1 };
  const auto tripplet { extract(str, current_index, 1) };
  const auto encoded { encodeTripplet(tripplet[0]) };
  append(encoded, 2);
  appendPadding(2);
}
void Base64Encoder::appendPadding(size_t number_of_padding) { container.append(number_of_padding, '='); }

}  // namespace home::crypto