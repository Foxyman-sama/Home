#ifndef HOME_ADAPTERS_BINARY_EXTRACTOR_HPP
#define HOME_ADAPTERS_BINARY_EXTRACTOR_HPP

#include <vector>

namespace home::adapters {
class BinaryExtractor {
private:
  std::vector<char> binary_data;
  size_t offset;

  size_t extractSize();
  std::vector<char> extractData(size_t size_of_data);
  void increaseOffset(size_t value);

public:
  void setBinaryDataAndResetOffset(const std::vector<char> &binary_data) noexcept;

  std::vector<char> extract();
};
}

#endif
