#ifndef HTML_FILES_HPP
#define HTML_FILES_HPP

#include <boost/beast/http/file_body.hpp>
#include <string>
#include <unordered_map>

namespace home::webserver {

class HTMLContainer {
 private:
  std::unordered_map<std::string_view, std::string_view> html_by_targetFile;

 public:
  void emplace(const std::string_view &targetFile, const std::string_view &filepath);

  boost::beast::http::file_body::value_type get(const std::string_view &targetFile);

  bool isContained(const std::string_view &targetFile) const noexcept;
};

}  // namespace home::webserver

#endif