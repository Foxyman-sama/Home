#include "html_files.hpp"

namespace home::webserver {

void HTMLContainer::emplace(const std::string_view &targetFile, const std::string_view &filepath) {
  html_by_targetFile[targetFile] = filepath;
}

boost::beast::http::file_body::value_type HTMLContainer::get(const std::string_view &targetFile) {
  boost::beast::http::file_body::value_type file;
  boost::beast::error_code ec;
  file.open(html_by_targetFile[targetFile].data(), boost::beast::file_mode::scan, ec);
  return file;
}

bool HTMLContainer::isContained(const std::string_view &targetFile) const noexcept {
  return html_by_targetFile.contains(targetFile);
}

}  // namespace home::webserver