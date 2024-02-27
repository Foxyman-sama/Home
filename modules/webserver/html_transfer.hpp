#ifndef HTML_TRANSFER_HPP
#define HTML_TRANSFER_HPP

#include "net_lib.hpp"

namespace home::webserver {

class Receiver {
 private:
  net::flat_buffer buffer;
  std::optional<net::http::request_parser<net::http::string_body>> parser;
  net::http::request<net::http::string_body> request;

 public:
  void receive(net::Socket &socket);

  net::http::verb getMethod() const noexcept;
  std::string_view getTarget() const noexcept;
  net::http::request<net::http::string_body> &getRequest() noexcept;
  std::string &getBody() noexcept;
};

class Sender {
 public:
  void send(net::Socket &socket, net::http::file_body::value_type &&file,
            net::http::status status = net::http::status::ok);

  void send(net::Socket &socket, const std::string_view &str, net::http::status status = net::http::status::ok);

 private:
  net::http::response<net::http::file_body> makeResponseHeaderWithFileBody(net::http::status status);

  net::http::response<net::http::string_body> makeResponseHeaderWithStringBody(net::http::status status);
};

}  // namespace home::webserver
#endif