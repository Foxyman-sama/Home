#ifndef HOME_FILES_STRUCT_HPP
#define HOME_FILES_STRUCT_HPP

#include <vector>
#include <string>

namespace home::interactor {
using File = std::pair<std::string, std::vector<char>>;
using Files = std::vector<File>;
}

#endif
