#ifndef TEST_WEBSERVER_HPP
#define TEST_WEBSERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>

#include "modules/core/controller.hpp"
#include "utility/reader.hpp"

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
  Controller& controller;

 public:
  WebServer(net::io_context& io, int port, Controller& controller)
      : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } }, controller { controller } {}

  net::tcp::socket accept() { return acceptor.accept(); }

  void handle(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request<net::http::string_body> req;
    net::http::read(socket, buffer, req);
    if (req.target() == "/") {
      net::http::file_body::value_type body;
      net::error_code ec;
      body.open("build/index.html", net::file_mode::scan, ec);

      net::http::response<net::http::file_body> res { std::piecewise_construct, std::make_tuple(std::move(body)),
                                                      std::make_tuple(net::http::status::ok, req.version()) };
      res.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
      res.set(net::http::field::content_type, "text/html");
      // TODO - continue
    }
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

    void handle(std::string& actual) {
      std::thread { [&, this] {
        net::http::request<net::http::string_body> req { net::http::verb::get, "/", 10 };
        req.set(net::http::field::host, ip);
        req.set(net::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(net::http::field::content_length, std::to_string(4));
        req.body() = "Test";

        net::error_code ec;
        net::http::write(stream, req, ec);

        net::flat_buffer buffer;
        net::http::response<net::http::string_body> res;
        net::http::read(stream, buffer, res);
        actual = res.body().data();
      } }.detach();
    }
  };

  net::io_context io;
  std::unique_ptr<WebServer> server;
  std::unique_ptr<TestConnection> connection;
  std::string actual;
  std::string expected;
  Reader reader;
  MockController controller;

 public:
  void givenExpectedHTMLFile(const std::string& expected) {
    server.reset(new WebServer { io, 9090, controller });
    connection.reset(new TestConnection { "127.0.0.1", "9090" });
    reader.open("build/", expected);
    this->expected = reader.createStreamAndReadFile(expected);
  }

  void whenServerIsHanding() {
    connection->connect();

    auto socket { server->accept() };
    connection->handle(actual);
    server->handle(socket);
  }

  void thenActualShouldBeEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(WebServerTest, Get_request_return_index_html) {
  givenExpectedHTMLFile("index.html");
  whenServerIsHanding();
  thenActualShouldBeEqualExpected();
}

#endif