#include "webserver.hpp"

namespace home::webserver {

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
    sender.send(socket, ErrorMessages::bad_target, net::http::status::bad_request);
  }
}
void WebServer::readAndSendHTML(net::tcp::socket& socket, const std::string_view& path) {
  auto file { readFile(path) };
  sender.send(socket, file, net::http::status::ok);
}
net::http::file_body::value_type WebServer::readFile(const std::string_view& path) {
  net::http::file_body::value_type file;
  net::error_code ec;
  file.open(path.data(), net::file_mode::scan, ec);
  return file;
}

void WebServer::handleAndSendInfo(net::tcp::socket& socket) {
  auto body { receiver.getBody() };
  if (isHTMLBroken(body) == true) {
    sender.send(socket, ErrorMessages::bad_request, net::http::status::bad_request);
  }

  auto info { controller.save(receiver.getBody()) };
  auto formated { makeStringWithInfo(info) };
  sender.send(socket, formated, net::http::status::ok);
}
std::string WebServer::makeStringWithInfo(const HashTable<std::string, std::string>& info) {
  std::string result;
  for (auto&& [key, value] : info) {
    result += std::format("{} - {}\n", key, value);
  }

  return result;
}

}  // namespace home::webserver