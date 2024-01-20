#ifndef TEST_WEBSERVER_HPP
#define TEST_WEBSERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>

#include "modules/core/controller.hpp"

using namespace testing;
using namespace home::controller;

namespace net {

using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;

}  // namespace net

class MockController : public Controller {
 public:
} class WebServer {
 private:
  net::tcp::acceptor acceptor;

 public:
  WebServer(net::io_context& io, int port) : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } } {}

  net::tcp::socket accept() { return acceptor.accept(); }

  void handle(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request<net::http::string_body> res;
    net::http::read(socket, buffer, res);
    std::cout << res << '\n';
  }
};

class WebServerTest : public Test {
 private:
  class TestConnection {
   private:
    net::io_context io;
    net::tcp_stream stream;
    std::string ip;
    std::string port;

   public:
    TestConnection(const std::string& ip, const std::string& port)
        : stream { io }, ip { std::move(ip) }, port { std::move(port) } {
      std::thread th { [this] {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        net::tcp::resolver resolver { io };
        const auto endpoint { resolver.resolve(this->ip, this->port) };
        stream.connect(endpoint);
      } };
      th.detach();
    }
    ~TestConnection() {
      net::error_code ec;
      stream.socket().shutdown(net::tcp::socket::shutdown_both, ec);
    }

    void sendStringRequest(std::string message) {
      std::thread th { [=, this] {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        net::http::request<net::http::string_body> req { net::http::verb::get, "/", 10 };
        req.set(net::http::field::host, ip);
        req.set(net::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.body() = message;
        net::http::write(stream, req);
      } };
      th.detach();
    }
  };

  net::io_context io;
  std::unique_ptr<WebServer> server;
  std::unique_ptr<TestConnection> connection;
  net::tcp::socket socket { io };
  std::string message;

 public:
  void givenPortAndMessage(const std::string& port, const std::string& message) {
    server.reset(new WebServer { io, std::stoi(port) });
    connection.reset(new TestConnection { "127.0.0.1", port });
    this->message = message;
  }

  void whenServerIsAcceptingConnection() { socket = server->accept(); }
  void whenServerIsSendingMessage() { server->send(socket, message); }

  void thenSocketShouldBeOpen() { ASSERT_EQ(socket.is_open(), true); }
};

TEST_F(WebServerTest, Connecting_is_correct) {
  givenPortAndMessage("9090", "");
  whenServerIsAcceptingConnection();
  thenSocketShouldBeOpen();
}
TEST_F(WebServerTest, Sending_message_is_correct) {
  givenPortAndMessage("9090", "Hello");
  whenServerIsAcceptingConnection();
  whenServerIsSendingMessage();
  thenSocketShouldBeOpen();
}

#endif