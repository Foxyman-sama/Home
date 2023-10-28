#ifndef HOME_JSON_HPP
#define HOME_JSON_HPP

#include <string>
#include <vector>

namespace home::adapters {
class JSON {
public:
  std::string command;
  std::vector<std::string> filenames;
};
}

#endif
