#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <boost/beast.hpp>
#include <optional>

#include "controller.hpp"

namespace home::webserver {

namespace net {

using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;

}  // namespace net

class Receiver {
 private:
  net::flat_buffer buffer;
  std::optional<net::http::request_parser<net::http::string_body>> parser;
  net::http::request<net::http::string_body> request;

 public:
  void receive(net::tcp::socket& socket) {
    parser.emplace();
    parser->body_limit(100'000'000);
    net::http::read(socket, buffer, *parser);
    request = parser->release();
  }

  constexpr net::http::verb getMethod() const noexcept { return request.method(); }
  constexpr std::string_view getTarget() const noexcept { return request.target(); }
  net::http::request<net::http::string_body>& getRequest() noexcept { return request; }
  std::string& getBody() noexcept { return request.body(); }
};
class Sender {
 public:
  void send(net::tcp::socket& socket, net::http::file_body::value_type& file,
            net::http::status status = net::http::status::ok) {
    auto response { makeResponseHeader<net::http::file_body>(status) };
    response.content_length(file.size());
    response.body() = std::move(file);
    net::http::write(socket, response);
  }
  void send(net::tcp::socket& socket, const std::string_view& str, net::http::status status = net::http::status::ok) {
    auto response { makeResponseHeader<net::http::string_body>(status) };
    response.content_length(str.size());
    response.body() = str;
    net::http::write(socket, response);
  }

 private:
  template <typename ResponseType>
  net::http::response<ResponseType> makeResponseHeader(net::http::status status) {
    net::http::response<ResponseType> response { status, 10 };
    response.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(net::http::field::content_type, "text/html");
    return response;
  }
};
class WebServer {
 private:
  net::tcp::acceptor acceptor;
  controller::Controller& controller;
  Receiver receiver;
  Sender sender;

 public:
  explicit WebServer(net::io_context& io, unsigned short port, controller::Controller& controller);

  net::tcp::socket accept();

  void handle(net::tcp::socket& socket);

 private:
  void sendByTarget(net::tcp::socket& socket);
  void readAndSendHTML(net::tcp::socket& socket, const std::string_view& path);
  net::http::file_body::value_type readFile(const std::string_view& path);
  template <typename ResponseType = net::http::string_body>
  void send(net::tcp::socket& socket, auto&& answer, net::http::status status = net::http::status::ok);
  template <typename ResponseType = net::http::string_body>
  net::http::response<ResponseType> makeResponse(auto&& body, net::http::status status = net::http::status::ok);

  void handleAndSendInfo(net::tcp::socket& socket);
  std::string makeStringWithInfo(const HashTable<std::string, std::string>& info);
};

template <typename ResponseType>
void WebServer::send(net::tcp::socket& socket, auto&& answer, net::http::status status) {
  auto response { makeResponse<ResponseType>(answer, status) };
  net::http::write(socket, response);
}
template <typename ResponseType>
net::http::response<ResponseType> WebServer::makeResponse(auto&& body, net::http::status status) {
  net::http::response<ResponseType> response { status, 10 };
  response.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
  response.set(net::http::field::content_type, "text/html");
  response.content_length(body.size());
  response.body() = std::move(body);
  return response;
}

}  // namespace home::webserver

#endif