#ifndef HOME_DESERIALIZER_IMPL_HPP
#define HOME_DESERIALIZER_IMPL_HPP

#include "adapters_api.hpp"
#include "deserializer.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace home::adapters {
class AdaptersAPI DeserializerImpl
  : public Deserializer {
private:
  using ptree = boost::property_tree::ptree; 

  std::vector<char> serialized_data;
  size_t offset;
  ptree json;

  void setSerializedDataAndClearOffset(const std::vector<char> &serialized_data);
  void readJSONFromBinary();
  interactor::Files readFilesFromBinary();
  std::pair<std::string, std::vector<char>> makeFileFromBinary(auto &&filename);
  std::vector<char> extractFromBinary();

public:
  interactor::Files deserialize(const std::vector<char> &serialized_data) override;
};
}

#endif
