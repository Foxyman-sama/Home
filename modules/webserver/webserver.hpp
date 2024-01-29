#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <boost/beast.hpp>

#include "controller.hpp"

namespace home::webserver {

namespace net {

using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;

}  // namespace net

class WebServer {
 private:
  net::tcp::acceptor acceptor;
  controller::Controller& controller;

 public:
  explicit WebServer(net::io_context& io, unsigned short port, controller::Controller& controller);

  net::tcp::socket accept();

  void handle(net::tcp::socket& socket);

 private:
  net::http::request<net::http::string_body> receive(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request_parser<net::http::string_body> request;
    request.body_limit(100'000'000);
    net::http::read(socket, buffer, request);
    return request.release();
  }
  constexpr bool isRequest(const net::http::request<net::http::string_body>& request,
                           net::http::verb verb) const noexcept;
  void sendByTarget(net::tcp::socket& socket, const std::string_view& target);
  void sendHTML(net::tcp::socket& socket, const std::string_view& path);
  net::http::file_body::value_type readFile(const std::string_view& path);
  template <typename ResponseType = net::http::string_body>
  void sendAnswer(net::tcp::socket& socket, auto&& answer, net::http::status status) {
    auto response { makeResponse<ResponseType>(answer, status) };
    net::http::write(socket, response);
  }
  template <typename ResponseType = net::http::string_body>
  net::http::response<ResponseType> makeResponse(auto&& body, net::http::status status = net::http::status::ok) {
    net::http::response<ResponseType> response { status, 10 };
    response.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(net::http::field::content_type, "text/html");
    response.content_length(body.size());
    response.body() = std::move(body);
    return response;
  }
  std::string makeStringWithInfo(const HashTable<std::string, std::string>& info);
};

}  // namespace home::webserver

#endif