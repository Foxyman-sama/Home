#ifndef HOME_DESERIALIZER_IMPL_HPP
#define HOME_DESERIALIZER_IMPL_HPP

#include "adapters_api.hpp"
#include "deserializer.hpp"
#include "binary_manipulation/binary_extractor.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace home::adapters {
class AdaptersAPI DeserializerImpl
  : public Deserializer {
private:
  using JSON = boost::property_tree::ptree; 
  using File = interactor::File;
  using Files = interactor::Files;

  BinaryExtractor extractor;

  JSON deserializeJSON();
  std::stringstream extractJSONAndMakeStream();

  Files deserializeFiles(const JSON &json);
  std::string extractStringFromJSONProperty(auto &&json_property);
  File extractAndMakeFile(const std::string &filename);

public:
  interactor::Files deserialize(const std::vector<char> &serialized_data) override;
};
}

#endif