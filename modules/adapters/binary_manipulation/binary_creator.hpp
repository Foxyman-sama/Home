#ifndef HOME_ADAPTERS_BINARY_CREATOR_HPP
#define HOME_ADAPTERS_BINARY_CREATOR_HPP

#include <vector>
#include <string>

namespace home::adapters {

class BinaryCreator {
public:
  static std::vector<char> createBinaryDataIncludingSize(const std::string &data, size_t size_of_data) {
    std::vector<char> result { };
    result.resize(sizeof(size_of_data) + size_of_data);
    std::memcpy(result.data(), &size_of_data, sizeof(size_of_data));
    std::memcpy(result.data() + sizeof(size_of_data), data.data(), size_of_data);
    return result;
  }
};

}

#endif
