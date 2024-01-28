#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <algorithm>
#include <ranges>
#include <vector>

namespace home::crypto {

template <typename Container>
class Crypto {
 protected:
  Container container;
  size_t data_size;

  virtual void setUp(const Container &container) noexcept = 0;

  template <typename ResponseType, size_t size>
  void append(const std::array<ResponseType, size> &src, size_t amount) {
    std::ranges::copy_n(src.begin(), amount, std::back_inserter(container));
  }
};

template <typename ResponseType>
ResponseType extract(const ResponseType &data, size_t start, size_t amount) {
  const auto pos_of_extracted { std::begin(data) + start };
  return { pos_of_extracted, pos_of_extracted + amount };
}

}  // namespace home::crypto
#endif