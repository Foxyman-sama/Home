#include "webserver.hpp"

namespace home::webserver {

WebServer::WebServer(net::io_context &io, unsigned short port, controller::Controller &controller)
    : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } }, controller { controller } {}

net::Socket WebServer::accept() { return acceptor.accept(); }

void WebServer::handle(net::Socket &socket) {
  receiver.receive(socket);
  if (receiver.getMethod() == net::http::verb::get) {
    handleGet(socket);
  } else if (receiver.getMethod() == net::http::verb::post) {
    handlePost(socket);
  } else {
    sender.send(socket, ErrorMessages::bad_request, net::http::status::bad_request);
  }
}

void WebServer::handleGet(net::Socket &socket) {
  if (receiver.getTarget() == Targets::default_target) {
    readAndSendHTML(socket, HTMLPaths::index);
  } else {
    sender.send(socket, ErrorMessages::bad_target, net::http::status::bad_request);
  }
}
void WebServer::readAndSendHTML(net::Socket &socket, const std::string_view &path) {
  sender.send(socket, readFile(path), net::http::status::ok);
}
net::http::file_body::value_type WebServer::readFile(const std::string_view &path) {
  net::http::file_body::value_type file;
  net::error_code ec;
  file.open(path.data(), net::file_mode::scan, ec);
  return file;
}

void WebServer::handlePost(net::Socket &socket) {
  auto body { receiver.getBody() };
  if (isHTMLBroken(body) == true) {
    sender.send(socket, ErrorMessages::bad_request, net::http::status::bad_request);
  } else {
    auto info { controller.save(receiver.getBody()) };
    sender.send(socket, makeStringWithInfo(info), net::http::status::ok);
  }
}
std::string WebServer::makeStringWithInfo(const HashTable<std::string, std::string> &info) {
  std::string result;
  for (auto &&[key, value] : info) {
    result += std::format("{} - {}\n", key, value);
  }

  return result;
}

}  // namespace home::webserver