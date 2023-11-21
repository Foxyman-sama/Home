#include "web_write_controller.hpp"

namespace home::adapters {
void WebWriteController::write(const std::vector<char> &web_data) { 
  interactor::Files deserialized_files { deserializer.deserialize(web_data) };
  boundary.writeFiles(deserialized_files); // LET`S KISS!!!
}
}