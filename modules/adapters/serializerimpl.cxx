#include "serializerimpl.hpp"
#include "serializerimpl.hpp"

namespace home::adapters {

std::vector<char> SerializerImpl::serialize(const interactor::Files &files) {
  JSON json { makeJSONContainsFilenames(files) };
  std::string formated_json { makeStringFromJSON(json) };
  std::vector<char> result { createBinaryDataFromJSON(formated_json) };
  for (auto &&[filename, filedata]: files) {
    result.append_range(createBinaryDataFromString(filedata.data(), filedata.size()));
  }

  return result;
}
SerializerImpl::JSON SerializerImpl::makeJSONContainsFilenames(const Files &files) {
  JSON json { };
  JSON array { };
  for (auto &&[filename, _]: files) {
    array.push_back(makeJSONArrayElementFromString(filename));
  }

  json.add_child("files", array);
  return json;
}
std::pair<std::string, SerializerImpl::JSON> SerializerImpl::makeJSONArrayElementFromString(const std::string &str) {
  JSON array_element { };
  array_element.put("", str);
  return { "", array_element };
}
std::string SerializerImpl::makeStringFromJSON(const JSON &json) {
  std::stringstream ss { };
  boost::property_tree::write_json(ss, json);
  return ss.str();
}
std::vector<char> SerializerImpl::createBinaryDataFromJSON(const std::string &json) {
  std::vector<char> binary_data { };
  binary_data.append_range(createBinaryDataFromString(json, json.size()));
  return binary_data;
}
std::vector<char> SerializerImpl::createBinaryDataFromString(const std::string &str, size_t size_of_str) {
  return BinaryCreator::createBinaryDataIncludingSize(str.data(), size_of_str);
}

}