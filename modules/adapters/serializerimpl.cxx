#include "serializerimpl.hpp"

namespace home::adapters {

std::vector<char> SerializerImpl::serialize(const interactor::Files &files) {
  JSON json { makeJSONBasedOnFiles(files) };
  std::vector<char> serialized_data { makeBinaryDataFromJSON(json) };
  for (auto &&[_, filedata]: files) {
    if (filedata.size() > 0) {
      serialized_data.append_range(makeBinaryDataFromString(filedata.data(), filedata.size()));
    }
  }

  return serialized_data;
}
SerializerImpl::JSON SerializerImpl::makeJSONBasedOnFiles(const Files &files) {
  JSON json { };
  json.add_child("files", makeJSONArrayContainsFilenames(files));
  return json;
}
SerializerImpl::JSON SerializerImpl::makeJSONArrayContainsFilenames(const Files &files) {
  JSON array { };
  for (auto &&[filename, _]: files) {
    array.push_back(makeJSONArrayElementFromString(filename));
  }

  return array;
}
std::pair<std::string, SerializerImpl::JSON> SerializerImpl::makeJSONArrayElementFromString(const std::string &str) {
  JSON array_element { };
  array_element.put("", str);
  return { "", array_element };
}
std::vector<char> SerializerImpl::makeBinaryDataFromJSON(const JSON &json) {
  std::stringstream ss { };
  boost::property_tree::write_json(ss, json);
  return makeBinaryDataFromString(ss.str(), ss.str().size());
}
std::vector<char> SerializerImpl::makeBinaryDataFromString(const std::string &str, size_t size_of_str) {
  return BinaryCreator::createBinaryDataIncludingSize(str, size_of_str);
}

}