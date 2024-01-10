#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <vector>

namespace home::crypto {

class Encoder {
 public:
  virtual std::vector<char> encode(const std::vector<char> &data) = 0;
};

}  // namespace home::crypto

#endif