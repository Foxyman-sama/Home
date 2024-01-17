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

  template <typename T, size_t size>
  void append(const std::array<T, size> &src, size_t amount) {
    std::ranges::copy_n(src.begin(), amount, std::back_inserter(container));
  }
};

template <typename T>
T extract(const T &data, size_t start, size_t amount) {
  const auto pos_of_extracted { std::begin(data) + start };
  return { pos_of_extracted, pos_of_extracted + amount };
}

}  // namespace home::crypto
#endif