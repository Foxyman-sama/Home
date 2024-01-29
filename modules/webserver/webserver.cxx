#include "webserver.hpp"

namespace home::webserver {

struct ErrorMessages {
  static constexpr std::string_view bad_target { "Unknown target" };
  static constexpr std::string_view bad_request { "Unknown method" };
  static constexpr std::string_view empty_post { "The post request is empty" };
};
struct HTMLPaths {
  static constexpr std::string_view html_index { "build/index.html" };
};

WebServer::WebServer(net::io_context& io, unsigned short port, controller::Controller& controller)
    : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } }, controller { controller } {}

net::tcp::socket WebServer::accept() { return acceptor.accept(); }

void WebServer::handle(net::tcp::socket& socket) {
  auto request { receive(socket) };
  if (isRequest(request, net::http::verb::get)) {
    sendByTarget(socket, request.target());
  } else if (isRequest(request, net::http::verb::post)) {
    if (request.body().find("filename") == std::string::npos) {
      sendAnswer(socket, ErrorMessages::empty_post, net::http::status::bad_request);
    } else {
      auto info { controller.save(request.body()) };
      auto formated { makeStringWithInfo(info) };
      sendAnswer(socket, formated, net::http::status::ok);
    }
  } else {
    auto response { makeResponse(ErrorMessages::bad_request) };
    sendAnswer(socket, ErrorMessages::bad_request, net::http::status::bad_request);
  }
}
constexpr bool WebServer::isRequest(const net::http::request<net::http::string_body>& request,
                                    net::http::verb verb) const noexcept {
  return request.method() == verb;
}
void WebServer::sendByTarget(net::tcp::socket& socket, const std::string_view& target) {
  if (target == "/") {
    sendHTML(socket, HTMLPaths::html_index);
  } else {
    sendAnswer(socket, ErrorMessages::bad_target, net::http::status::bad_request);
  }
}
void WebServer::sendHTML(net::tcp::socket& socket, const std::string_view& path) {
  auto file { readFile(path) };
  sendAnswer<net::http::file_body>(socket, file, net::http::status::ok);
}
net::http::file_body::value_type WebServer::readFile(const std::string_view& path) {
  net::http::file_body::value_type file;
  net::error_code ec;
  file.open(path.data(), net::file_mode::scan, ec);
  return file;
}
std::string WebServer::makeStringWithInfo(const HashTable<std::string, std::string>& info) {
  std::string result;
  for (auto&& [key, value] : info) {
    result += std::format("{} - {}\n", key, value);
  }

  return result;
}

}  // namespace home::webserver