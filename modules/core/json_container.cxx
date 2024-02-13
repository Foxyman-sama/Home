#include "json_container.hpp"

namespace home::container {

JSONContainer::JSONContainer(const std::string_view &path) : path { path } {
  std::ifstream fin { path.data() };
  if (fin.is_open() == true) {
    json::read_json(fin, json);
  }
}

void JSONContainer::write(const std::string &filename, const std::string &filedata) { json.put(filename, filedata); }

std::string JSONContainer::read(const std::string &filename) { return json.get<std::string>(filename); }

std::vector<std::string> JSONContainer::getSavedFilenames() {
  std::vector<std::string> result;
  for (const auto &node : json) {
    result.emplace_back(node.first);
  }

  return result;
}

void JSONContainer::extractToFile() noexcept {
  if (path.empty() == false) {
    std::ofstream fout { path.data() };
    json::write_json(fout, json);
  }
}

}  // namespace home::container