#ifndef TEST_WEBSERVER_HPP
#define TEST_WEBSERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <format>
#include <future>
#include <memory>

#include "modules/core/controller_impl.hpp"
#include "modules/core/hash_table.hpp"
#include "utility/generators.hpp"
#include "utility/reader.hpp"

using namespace testing;
using namespace home;
using namespace controller;

namespace net {

using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;

}  // namespace net

class MockController : public Controller {
 public:
  MOCK_METHOD((HashTable<std::string, std::string>), save, (const std::string&), (override));
};
class WebServer {
 private:
  static constexpr std::string_view bad_target_message { "Unknown target" };
  static constexpr std::string_view bad_request_message { "Unknown method" };
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
      auto answer { controller.save(request.body()) };
      std::string formated;
      for (auto&& [key, value] : answer) {
        formated += std::format("{} - {}\n", key, value);
      }

      auto response { makeResponse(formated) };
      send(socket, response);
    } else {
      auto response { makeResponse(bad_request_message) };
      send(socket, response);
    }
  }

 private:
  constexpr bool isRequest(const auto& request, net::http::verb verb) const noexcept {
    return request.method() == verb;
  }

  net::http::request<net::http::string_body> receive(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request<net::http::string_body> req;
    net::http::read(socket, buffer, req);
    return req;
  }

  void sendByTarget(auto& socket, const auto& target) {
    if (target == "/") {
      auto file { readFile("build/index.html") };
      auto response { makeResponse<net::http::file_body>(std::move(file)) };
      send(socket, response);
    } else {
      auto response { makeResponse(bad_target_message, net::http::status::bad_request) };
      send(socket, response);
    }
  }
  net::http::file_body::value_type readFile(const auto& filename) {
    net::http::file_body::value_type file;
    net::error_code ec;
    file.open(filename, net::file_mode::scan, ec);
    return file;
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
  void send(auto& socket, auto& response) { net::http::write(socket, response); }
};
class TestConnection {
 private:
  net::io_context io;
  net::tcp_stream stream;
  std::string ip;
  std::string port;

 public:
  TestConnection(const std::string& ip = "127.0.0.1", const std::string& port = "9090")
      : stream { io }, ip { ip }, port { port } {}
  ~TestConnection() {
    net::error_code ec;
    stream.socket().shutdown(net::tcp::socket::shutdown_both, ec);
  }

  void connect() {
    net::tcp::resolver resolver { io };
    const auto endpoint { resolver.resolve(ip, port) };
    stream.connect(endpoint);
  }

  std::string get(const std::string& target) {
    auto request { makeRequestHeader(net::http::verb::get, target) };
    net::http::write(stream, request);

    auto response { read() };
    return response.body();
  }

  std::string post(const std::string& target, const std::string& body) {
    auto request { makeRequestHeader(net::http::verb::post, target) };
    request.content_length(body.size());
    request.body() = body;
    net::http::write(stream, request);

    auto response { read() };
    return response.body();
  }

 private:
  net::http::request<net::http::string_body> makeRequestHeader(net::http::verb verb, const std::string& target) {
    net::http::request<net::http::string_body> request { verb, target, 10 };
    request.set(net::http::field::host, ip);
    request.set(net::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    return request;
  }

  net::http::response<net::http::string_body> read() {
    net::flat_buffer buffer;
    net::http::response<net::http::string_body> response;
    net::http::read(stream, buffer, response);
    return response;
  }
};
class WebServerTest : public Test {
 protected:
  net::io_context io;
  MockController controller;
  WebServer server;
  TestConnection connection;

  WebServerTest() : server { io, 9090, controller } {}
};
class WebServerGetTest : public WebServerTest {
 private:
  std::string target;
  std::string actual;
  std::string expected;
  Reader reader;

 public:
  void givenTargetAndExpected(const std::string& target, const std::string& expected) {
    this->target = target;
    this->expected = expected;
  }

  void whenClientIsGetting() {
    auto wait_connection { std::async(std::launch::async, &TestConnection::connect, &connection) };
    auto socket { server.accept() };
    wait_connection.wait();

    auto wait_getting { std::async(std::launch::async, &TestConnection::get, &connection, target) };
    server.handle(socket);
    actual = wait_getting.get();
  }

  void thenActualAndExpectedDataShouldBeEqual() { ASSERT_EQ(actual, expected); }
};

TEST_F(WebServerGetTest, Correct_request_return_index_html) {
  givenTargetAndExpected("/", readFile("build/index.html"));
  whenClientIsGetting();
  thenActualAndExpectedDataShouldBeEqual();
}
TEST_F(WebServerGetTest, Request_with_bad_target_return_error) {
  givenTargetAndExpected("@", "Unknown target");
  whenClientIsGetting();
  thenActualAndExpectedDataShouldBeEqual();
}

#endif