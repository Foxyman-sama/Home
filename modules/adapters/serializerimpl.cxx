#include "serializerimpl.hpp"

namespace home::adapters {

std::vector<char> SerializerImpl::serialize(const interactor::Files &files) {
  JSON json { };
  JSON array { };
  for (auto &&[filename, _]: files) {
    JSON array_element { };
    array_element.put("", filename);
    array.push_back({ "", array_element });
  }

  json.add_child("files", array);
  
  std::stringstream ss { };
  boost::property_tree::write_json(ss, json);

  std::vector<char> result { };
  result.append_range(BinaryCreator::createBinaryDataIncludingSize(ss.str().data(), ss.str().size()));
  for (auto &&[filename, filedata]: files) {
    result.append_range(BinaryCreator::createBinaryDataIncludingSize(filedata.data(), filedata.size()));
  }

  return result;
}

}