#include "binary_extractor.hpp"

namespace home::adapters {

std::vector<char> BinaryExtractor::extract() {
  if (offset >= binary_data.size()) {
    throw std::exception { "Serialized data isn't correct" };
  }

  size_t extracted_size { extractSize() };
  std::vector<char> extracted_data { extractData(extracted_size) };
  return extracted_data;
}
size_t BinaryExtractor::extractSize() {
  size_t size { };
  std::memcpy(&size, binary_data.data() + offset, sizeof(size_t));
  increaseOffset(sizeof(size_t));
  return size;
}
std::vector<char> BinaryExtractor::extractData(size_t size_of_data) {
  std::vector<char> data { };
  data.resize(size_of_data);
  std::memcpy(data.data(), binary_data.data() + offset, size_of_data);
  increaseOffset(size_of_data);
  return data;
}
void BinaryExtractor::increaseOffset(size_t value) {
  offset += value;
}

void BinaryExtractor::setBinaryDataAndResetOffset(const std::vector<char> &binary_data) noexcept {
  this->binary_data = binary_data;
  this->offset = 0;
}

}