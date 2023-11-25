#include "deserializerimpl.hpp"

namespace home::adapters {
interactor::Files DeserializerImpl::deserialize(const std::vector<char> &serialized_data) {
  setSerializedDataAndClearOffset(serialized_data);
  readJSONFromBinary();
  return readFilesFromBinary();
}
void DeserializerImpl::setSerializedDataAndClearOffset(const std::vector<char> &serialized_data) {
  this->serialized_data = serialized_data;
  this->offset = 0;
}
void DeserializerImpl::readJSONFromBinary() {
  auto binary_json { extractFromBinary() };
  std::stringstream ss { };
  ss.write(binary_json.data(), binary_json.size());
  boost::property_tree::read_json(ss, json);
}

interactor::Files DeserializerImpl::readFilesFromBinary() {
  interactor::Files files { };
  for (auto &&filename: json.get_child("files")) {
    files.emplace_back(makeFileFromBinary(filename));
  }

  return files;
}
std::pair<std::string, std::vector<char>> DeserializerImpl::makeFileFromBinary(auto &&filename) {
  auto data { extractFromBinary() };
  return { filename.second.get_value<std::string>(), data };
}
std::vector<char> home::adapters::DeserializerImpl::extractFromBinary() {
  size_t size { };
  std::memcpy(&size, serialized_data.data() + offset, sizeof(size_t));
  offset += sizeof(size_t);

  std::vector<char> data { };
  data.resize(size);
  std::memcpy(data.data(), serialized_data.data() + offset, size);
  offset += size;
  return data;
}
}