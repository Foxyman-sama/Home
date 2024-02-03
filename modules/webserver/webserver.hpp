#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <optional>

#include "../core/controller.hpp"
#include "html_definitions.hpp"
#include "html_transfer.hpp"

namespace home::webserver {

class WebServer {
 private:
  net::Acceptor acceptor;
  controller::Controller &controller;
  Receiver receiver;
  Sender sender;

 public:
  explicit WebServer(net::io_context &io, unsigned short port, controller::Controller &controller);

  net::Socket accept();

  void handle(net::Socket &socket);

 private:
  void handleGet(net::Socket &socket);
  void readAndSendHTML(net::Socket &socket, const std::string_view &path);
  net::http::file_body::value_type readFile(const std::string_view &path);

  void handlePost(net::Socket &socket);
  std::string makeStringWithInfo(const HashTable<std::string, std::string> &info);
};

}  // namespace home::webserver

#endif