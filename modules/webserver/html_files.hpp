#ifndef HTML_FILES_HPP
#define HTML_FILES_HPP

class HTMLs {
 private:
  struct HTMLPaths {
    static constexpr std::string_view index { "build/index.html" };
  };

 public:
  static std::string index;

  HTMLs() {}

 private:
  ::file_body::value_type WebServer::readFile(const std::string_view &path) {
    http::file_body::value_type file;
    net::error_code ec;
    file.open(path.data(), net::file_mode::scan, ec);
    return file;
  }
};
#endif