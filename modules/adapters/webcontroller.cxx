#include "webcontroller.hpp"

namespace home::adapters {
WebController::WebController(interactor::Boundary &boundary, JSONConverter &converter, Serializer &serializer,
                             Deserializer &deserializer) noexcept
  : boundary { boundary }, converter { converter }, serializer { serializer }, deserializer { deserializer } { }
std::optional<std::vector<char>> WebController::handle(const std::vector<char> &web_data) {
  if (web_data.empty() == true) {
    throw std::exception { "Data is empty!" };
  }

  auto files { deserializer.deserialize(web_data) };
  auto json { converter.convert(files[0]) };
  if (json.command == "read") {
    interactor::InputData input_data { };
    input_data.files.emplace<1>(interactor::FilenamesVector { json.filenames });
    boundary.readFiles(input_data);
  }
  else if (json.command == "write") {
    interactor::FilenameDataMap filedatas { };
    for (auto &&filename: json.filenames) {

    }

    interactor::InputData input_data { };
    input_data.files.emplace<0>(filedatas);
    boundary.readFiles(input_data);
  }

  return std::optional<std::vector<char>>();

}
}