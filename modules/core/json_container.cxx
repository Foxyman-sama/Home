#include "json_container.hpp"

namespace home::container {

JSONContainer::JSONContainer(const std::string_view& path) : path { path } {
  std::ifstream fin { path.data() };
  if (fin.is_open() == true) {
    json::read_json(fin, json);
  }
}

JSONContainer::~JSONContainer() {
  if (path.empty() == false) {
    std::ofstream fout { path.data() };
    json::write_json(fout, json);
  }
}

void JSONContainer::write(const std::string& filename, const std::string& filedata) { json.put(filename, filedata); }

std::string JSONContainer::read(const std::string& filename) { return json.get<std::string>(filename); }

}  // namespace home::container