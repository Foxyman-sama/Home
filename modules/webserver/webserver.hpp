#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <boost/beast.hpp>

#include "modules/core/controller.hpp"

namespace home::webserver {

namespace net {

using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;

}  // namespace net

struct ErrorMessages {
  static constexpr std::string_view bad_target { "Unknown target" };
  static constexpr std::string_view bad_request { "Unknown method" };
  static constexpr std::string_view empty_post { "The post request is empty" };
};
struct HTMLPaths {
  static constexpr std::string_view html_index { "build/index.html" };
};
class WebServer {
 private:
  net::tcp::acceptor acceptor;
  Controller& controller;

 public:
  explicit WebServer(net::io_context& io, unsigned short port, Controller& controller)
      : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } }, controller { controller } {}

  net::tcp::socket accept() { return acceptor.accept(); }

  void handle(auto& socket) {
    auto request { receive(socket) };
    if (isRequest(request, net::http::verb::get)) {
      sendByTarget(socket, request.target());
    } else if (isRequest(request, net::http::verb::post)) {
      if (request.body().find("filename") == std::string::npos) {
        sendAnswer(socket, ErrorMessages::empty_post, net::http::status::bad_request);
      } else {
        auto info { controller.save(request.body()) };
        auto formated { makeStringWithInfo(info) };
        sendAnswer(socket, formated, net::http::status::ok);
      }
    } else {
      auto response { makeResponse(ErrorMessages::bad_request) };
      sendAnswer(socket, ErrorMessages::bad_request, net::http::status::bad_request);
    }
  }

 private:
  net::http::request<net::http::string_body> receive(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request<net::http::string_body> req;
    net::http::read(socket, buffer, req);
    return req;
  }

  constexpr bool isRequest(const auto& request, net::http::verb verb) const noexcept {
    return request.method() == verb;
  }

  void sendByTarget(auto& socket, const auto& target) {
    if (target == "/") {
      sendHTML(socket, HTMLPaths::html_index);
    } else {
      sendAnswer(socket, ErrorMessages::bad_target, net::http::status::bad_request);
    }
  }
  void sendHTML(net::tcp::socket& socket, const std::string_view& path) {
    auto file { readFile(path) };
    sendAnswer<net::http::file_body>(socket, file, net::http::status::ok);
  }
  net::http::file_body::value_type readFile(const std::string_view& path) {
    net::http::file_body::value_type file;
    net::error_code ec;
    file.open(path.data(), net::file_mode::scan, ec);
    return file;
  }
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

  std::string makeStringWithInfo(const HashTable<std::string, std::string>& info) {
    std::string result;
    for (auto&& [key, value] : info) {
      result += std::format("{} - {}\n", key, value);
    }

    return result;
  }
};

}  // namespace home::webserver

#endif