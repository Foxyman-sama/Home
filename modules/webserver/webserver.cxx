#include "webserver.hpp"

namespace home::webserver {

struct ErrorMessages {
  static constexpr std::string_view bad_target { "Unknown target" };
  static constexpr std::string_view bad_request { "Unknown method" };
  static constexpr std::string_view empty_post { "The post request is empty" };
};
struct HTMLPaths {
  static constexpr std::string_view index { "build/index.html" };
};
struct Targets {
  static constexpr std::string_view default_target { "/" };
};

WebServer::WebServer(net::io_context& io, unsigned short port, controller::Controller& controller)
    : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } }, controller { controller } {}

net::tcp::socket WebServer::accept() { return acceptor.accept(); }

void WebServer::handle(net::tcp::socket& socket) {
  receiver.receive(socket);
  if (receiver.getMethod() == net::http::verb::get) {
    sendByTarget(socket);
  } else if (receiver.getMethod() == net::http::verb::post) {
    handleAndSendInfo(socket);
  } else {
    sender.send(socket, ErrorMessages::bad_request, net::http::status::bad_request);
  }
}

void WebServer::sendByTarget(net::tcp::socket& socket) {
  if (receiver.getTarget() == Targets::default_target) {
    readAndSendHTML(socket, HTMLPaths::index);
  } else {
    send(socket, ErrorMessages::bad_target, net::http::status::bad_request);
  }
}
void WebServer::readAndSendHTML(net::tcp::socket& socket, const std::string_view& path) {
  auto file { readFile(path) };
  send<net::http::file_body>(socket, file, net::http::status::ok);
}
net::http::file_body::value_type WebServer::readFile(const std::string_view& path) {
  net::http::file_body::value_type file;
  net::error_code ec;
  file.open(path.data(), net::file_mode::scan, ec);
  return file;
}

void WebServer::handleAndSendInfo(net::tcp::socket& socket) {
  auto info { controller.save(receiver.getBody()) };
  auto formated { makeStringWithInfo(info) };
  send(socket, formated, net::http::status::ok);
}
std::string WebServer::makeStringWithInfo(const HashTable<std::string, std::string>& info) {
  std::string result;
  for (auto&& [key, value] : info) {
    result += std::format("{} - {}\n", key, value);
  }

  return result;
}

}  // namespace home::webserver