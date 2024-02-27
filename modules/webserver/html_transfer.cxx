#include "html_transfer.hpp"

namespace home::webserver {

void Receiver::receive(net::Socket &socket) {
  parser.emplace();
  parser->body_limit(100'000'000);
  net::http::read(socket, buffer, *parser);
  request = parser->release();
}

net::http::verb Receiver::getMethod() const noexcept { return request.method(); }
std::string_view Receiver::getTarget() const noexcept { return request.target(); }
std::string Receiver::getTargetAfterSlash() const noexcept {
  return getTarget().substr(1, getTarget().size() - 1).data();
}
net::http::request<net::http::string_body> &Receiver::getRequest() noexcept { return request; }
std::string &Receiver::getBody() noexcept { return request.body(); }

void Sender::send(net::Socket &socket, net::http::file_body::value_type &&file, net::http::status status) {
  auto response { makeResponseHeader<net::http::file_body>(status) };
  response.content_length(file.size());
  response.body() = std::move(file);
  net::http::write(socket, response);
}
template <typename ResponseType>
net::http::response<ResponseType> Sender::makeResponseHeader(net::http::status status) {
  net::http::response<ResponseType> response { status, 10 };
  response.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
  response.set(net::http::field::content_type, "text/html");
  return response;
}

void Sender::send(net::Socket &socket, const std::string_view &str, net::http::status status) {
  auto response { makeResponseHeader<net::http::string_body>(status) };
  response.content_length(str.size());
  response.body() = str;
  net::http::write(socket, response);
}

}  // namespace home::webserver