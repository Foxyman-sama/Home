#include "webserver.hpp"

#include <format>

namespace home::webserver {

class TextFormater {
 public:
  static std::string makeStringWithInfo(const std::unordered_map<std::string, std::string> &info) {
    std::string result;
    for (auto &&[key, value] : info) {
      result += std::format("{} - {}\n", key, value);
    }

    return result;
  }

  static std::string makeParagraphs(const std::vector<std::string> &filenames) {
    std::string result;
    for (auto &&el : filenames) {
      result += std::format("<a href=\"127.0.0.1:9090/{}\">{}</a><br>", el, el);
    }

    return result;
  }
};

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
  if (target == "/list") {
    const auto list { TextFormater::makeParagraphs(controller.getSavedFilenames()) };
    sender.send(socket, list);
  } else if (container.isContained(target)) {
    sender.send(socket, container.get(target));
  } else if (const auto file { controller.get(target.substr(1, target.size() - 1).data()) }; file != "") {
    sender.send(socket, file);
  } else {
    sender.send(socket, ErrorMessages::bad_target, net::http::status::bad_request);
  }
}
void WebServer::handlePost(net::Socket &socket) {
  auto body { receiver.getBody() };
  if (isHTMLEmpty(body)) {
    sender.send(socket, ErrorMessages::empty_post, net::http::status::bad_request);
  } else if (isPostHTMLBroken(body)) {
    sender.send(socket, ErrorMessages::bad_request, net::http::status::bad_request);
  } else {
    auto info { controller.save(receiver.getBody()) };
    sender.send(socket, TextFormater::makeStringWithInfo(info), net::http::status::ok);
  }
}

}  // namespace home::webserver