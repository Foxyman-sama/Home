#include "deserializerimpl.hpp"

namespace home::adapters {

DeserializerImpl::Files DeserializerImpl::deserialize(const std::vector<char> &serialized_data) {
  extractor.setBinaryDataAndResetOffset(serialized_data);

  JSON json { deserializeJSON() };
  Files files { deserializeFiles(json) };
  return files;
}
DeserializerImpl::JSON DeserializerImpl::deserializeJSON() {
  std::stringstream ss { extractJSONAndMakeStream() };
  JSON json { };
  boost::property_tree::read_json(ss, json);
  return json;
}
std::stringstream DeserializerImpl::extractJSONAndMakeStream() {
  std::vector<char> binary_json { extractor.extract() };
  std::stringstream ss { };
  ss.write(binary_json.data(), binary_json.size());
  return ss;
}
DeserializerImpl::Files DeserializerImpl::deserializeFiles(const JSON &json) {
  Files files { };
  for (auto &&property: json.get_child("files")) {
    std::string filename { getStringFromJSONProperty(property) };
    files.emplace_back(extractAndMakeFile(filename));
  }

  return files;
}
std::string home::adapters::DeserializerImpl::getStringFromJSONProperty(auto &&json_property) {
  return json_property.second.get_value<std::string>();
}
DeserializerImpl::File DeserializerImpl::extractAndMakeFile(const std::string &filename) {
  std::vector<char> data { extractor.extract() };
  return { filename, data };
}

}