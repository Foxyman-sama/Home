#include "serializerimpl.hpp"

namespace home::adapters {

std::vector<char> SerializerImpl::serialize(const interactor::Files &files) {
  JSON json { makeJSONContainsFilenames(files) };
  std::string formated_json { makeStringFromJSON(json) };
  std::vector<char> result { };
  result.append_range(BinaryCreator::createBinaryDataIncludingSize(formated_json.data(), formated_json.size()));
  for (auto &&[filename, filedata]: files) {
    result.append_range(BinaryCreator::createBinaryDataIncludingSize(filedata.data(), filedata.size()));
  }

  return result;
}
SerializerImpl::JSON SerializerImpl::makeJSONContainsFilenames(const Files &files) {
  JSON json { };
  JSON array { };
  for (auto &&[filename, _]: files) {
    array.push_back({ "", makeJSONArrayElementFromString(filename) });
  }

  json.add_child("files", array);
  return json;
}
SerializerImpl::JSON SerializerImpl::makeJSONArrayElementFromString(const std::string &str) {
  JSON array_element { };
  array_element.put("", str);
  return array_element;
}
std::string SerializerImpl::makeStringFromJSON(const JSON &json) {
  std::stringstream ss { };
  boost::property_tree::write_json(ss, json);
  return ss.str();
}

}