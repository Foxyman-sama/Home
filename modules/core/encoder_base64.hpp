#ifndef ENCODER_BASE64_HPP
#define ENCODER_BASE64_HPP

#include <array>
#include <cstdint>
#include <string>

#include "crypto.hpp"

namespace home::crypto {

class Base64Encoder : public crypto::Crypto<std::string> {
 private:
  static constexpr std::array<char, 64> encode_table { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                                       'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                                       'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                                       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                                       '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
  static constexpr size_t tripplet_size { 3 };
  size_t number_of_tripplets;

 public:
  virtual std::string encode(const std::string &str);

 private:
  std::string tryEncode(const std::string &str);
  void setUp(const std::string &str) noexcept override;
  void encodeFullTripplets(const std::string &str);
  void encodeTrippletByIndex(const std::string &str, int index);
  std::array<char, 4> encodeTripplet(std::uint8_t a, std::uint8_t b = 0, std::uint8_t c = 0);

  void encodeRemainingCharsIfExist(const std::string &str);
  void encodeTwoRemainingChars(const std::string &str);
  void encodeOneRemainingChar(const std::string &str);
  void appendPadding(size_t number_of_padding);
};

}  // namespace home::crypto

#endif