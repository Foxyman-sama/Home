#include "webserver.hpp"

namespace home::webserver {

WebServer::WebServer(net::io_context &io, unsigned short port, controller::Controller &controller,
                     HTMLContainer &container)
    : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } },
      controller { controller },
      container { container } {}

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
  const auto target { receiver.getTarget() };
  if (container.isContained(target)) {
    sender.send(socket, container.get(target));
  } else {
    sender.send(socket, ErrorMessages::bad_target, net::http::status::bad_request);
  }
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
std::string WebServer::makeStringWithInfo(const std::unordered_map<std::string, std::string> &info) {
  std::string result;
  for (auto &&[key, value] : info) {
    result += std::format("{} - {}\n", key, value);
  }

  return result;
}

}  // namespace home::webserver