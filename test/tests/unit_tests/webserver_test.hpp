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
  MOCK_METHOD((HashTable<std::string, std::string>), save, (const std::string&), (override));
};
class WebServer {
 private:
  net::tcp::acceptor acceptor;

 public:
  WebServer(net::io_context& io, int port) : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } } {}

  net::tcp::socket accept() { return acceptor.accept(); }

  net::http::request<net::http::string_body> read(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request<net::http::string_body> req;
    net::http::read(socket, buffer, req);
    return req;
  }

  void write(net::tcp::socket& socket, net::http::response<net::http::file_body>& response) {
    net::http::write(socket, response);
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
    TestConnection(const std::string& ip, const std::string& port) : stream { io }, ip { ip }, port { port } {}
    ~TestConnection() {
      net::error_code ec;
      stream.socket().shutdown(net::tcp::socket::shutdown_both, ec);
    }

    void connect() {
      std::thread { [this] {
        net::tcp::resolver resolver { io };
        const auto endpoint { resolver.resolve(ip, port) };
        net::error_code ec;
        stream.connect(endpoint, ec);
      } }.detach();
    }

    void send(std::string message) {
      std::thread { [message, this] {
        net::http::request<net::http::string_body> req { net::http::verb::get, "/", 10 };
        req.set(net::http::field::host, ip);
        req.set(net::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(net::http::field::content_length, std::to_string(message.size()));
        req.body() = message;

        net::error_code ec;
        net::http::write(stream, req, ec);
      } }.detach();
    }

    net::http::response<net::http::string_body> read() {
      net::flat_buffer buffer;
      net::http::response<net::http::string_body> res;
      net::error_code ec;
      net::http::read(stream, buffer, res, ec);
      return res;
    }
  };

  net::io_context io;
  std::unique_ptr<WebServer> server;
  std::unique_ptr<TestConnection> connection;
  net::tcp::socket socket { io };
  net::http::request<net::http::string_body> req_server;
  net::http::response<net::http::string_body> res_client;
  std::string message;

 public:
  void givenMessage(const std::string& message) {
    server.reset(new WebServer { io, 9090 });
    connection.reset(new TestConnection { "127.0.0.1", "9090" });
    this->message = message;
  }

  void whenServerIsAcceptingConnection() {
    connection->connect();
    socket = server->accept();
  }
  void whenServerIsAcceptingRequest() {
    connection->send(message);
    req_server = server->read(socket);
  }
  void whenServerIsSendingResponse() {
    std::thread { [this] {
      net::http::file_body::value_type body;
      net::error_code ec;
      body.open(message.c_str(), net::file_mode::scan, ec);

      net::http::response<net::http::file_body> res { std::piecewise_construct, std::make_tuple(std::move(body)),
                                                      std::make_tuple(net::http::status::ok, 10) };
      res.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set(net::http::field::content_type, "text/html");
      res.content_length(body.size());
      server->write(socket, res);
    } }.detach();
    res_client = connection->read();
  }

  void thenSocketShouldBeOpen() { ASSERT_EQ(socket.is_open(), true); }
  void thenReceivedRequestShouldContainMessage() { ASSERT_EQ(req_server.body(), message); }
  void thenReceivedResponseShouldBeEqual() { /*ASSERT_EQ(req_server.body(), res_client.body());*/
  }
};

TEST_F(WebServerTest, Connecting_is_correct) {
  givenMessage("");
  whenServerIsAcceptingConnection();
  thenSocketShouldBeOpen();
}
TEST_F(WebServerTest, Sending_to_server_is_correct) {
  givenMessage("Test message!");
  whenServerIsAcceptingConnection();
  whenServerIsAcceptingRequest();
  thenReceivedRequestShouldContainMessage();
}
TEST_F(WebServerTest, Receiving_from_server_is_correct) {
  givenMessage("build/test.html");
  whenServerIsAcceptingConnection();
  whenServerIsSendingResponse();
  thenReceivedRequestShouldContainMessage();
}

#endif