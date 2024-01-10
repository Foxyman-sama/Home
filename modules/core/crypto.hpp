#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <algorithm>
#include <vector>

namespace home::crypto {

class Crypto {
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

}  // namespace home::crypto
#endif