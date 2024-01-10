#ifndef DECODER_HPP
#define DECODER_HPP

#include <vector>

namespace home::crypto {

class Decoder {
 public:
  virtual std::vector<char> decode(const std::vector<char> &data) = 0;
};

}  // namespace home::crypto
#endif