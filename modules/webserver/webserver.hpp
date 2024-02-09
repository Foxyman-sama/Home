#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <optional>

#include "../core/controller.hpp"
#include "html_definitions.hpp"
#include "html_files.hpp"
#include "html_transfer.hpp"

namespace home::webserver {

class WebServer {
 private:
  net::Acceptor acceptor;
  controller::Controller &controller;
  Receiver receiver;
  Sender sender;
  HTMLContainer &container;

 public:
  explicit WebServer(net::io_context &io, unsigned short port, controller::Controller &controller,
                     HTMLContainer &container);

  net::Socket accept();

  void handle(net::Socket &socket);

 private:
  void handleGet(net::Socket &socket);
  void handlePost(net::Socket &socket);
  std::string makeStringWithInfo(const std::unordered_map<std::string, std::string> &info);
};

}  // namespace home::webserver

#endif