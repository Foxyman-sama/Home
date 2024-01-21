#ifndef TEST_WEBSERVER_HPP
#define TEST_WEBSERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <condition_variable>
#include <memory>
#include <mutex>

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
};

class WebServerTest : public Test {
 private:
  class TestConnection {
   private:
    net::io_context io;
    net::tcp_stream stream;
    std::string ip;
    std::string port;
    std::string message;
    std::mutex mutex;
    std::condition_variable& cv;
    bool& ready;

   public:
    TestConnection(const std::string& ip, const std::string& port, const std::string& message,
                   std::condition_variable& cv, bool& ready)
        : stream { io }, ip { ip }, port { port }, message { message }, cv { cv }, ready { ready } {}
    ~TestConnection() {
      net::error_code ec;
      stream.socket().shutdown(net::tcp::socket::shutdown_both, ec);
    }

    void connect() {
      std::thread { [this] {
        std::unique_lock lk { mutex };
        cv.wait(lk, [this] { return ready == true; });
        std::this_thread::sleep_for(std::chrono::seconds(2));

        net::tcp::resolver resolver { io };
        const auto endpoint { resolver.resolve(this->ip, this->port) };
        stream.connect(endpoint);
        ready = false;
      } }.detach();
    }
    void send() {
      std::thread th { [this] {
        std::unique_lock lk { mutex };
        cv.wait(lk, [this] { return ready == true; });
        std::this_thread::sleep_for(std::chrono::seconds(3));

        net::http::request<net::http::string_body> req { net::http::verb::get, "/", 10 };
        req.set(net::http::field::host, ip);
        req.set(net::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(net::http::field::content_length, std::to_string(message.size()));
        req.body() = message;
        net::http::write(stream, req);
        ready = false;
      } };
      th.detach();
    }
  };

  net::io_context io;
  std::unique_ptr<WebServer> server;
  std::unique_ptr<TestConnection> connection;
  net::tcp::socket socket { io };
  net::http::request<net::http::string_body> received_req;
  std::string message;
  std::condition_variable cv;
  bool ready = false;

 public:
  void givenPortAndMessage(const std::string& port, const std::string& message) {
    server.reset(new WebServer { io, std::stoi(port) });
    connection.reset(new TestConnection { "127.0.0.1", port, message, cv, ready });
    this->message = message;
  }

  void whenServerIsAcceptingConnection() {
    connection->connect();
    unlock();
    socket = server->accept();
  }
  void whenServerIsAcceptingRequest() {
    connection->send();
    unlock();
    received_req = server->read(socket);
  }

  void thenSocketShouldBeOpen() { ASSERT_EQ(socket.is_open(), true); }
  void thenReceivedRequestShouldContainMessage() { ASSERT_EQ(received_req.body(), message); }

 private:
  void unlock() {
    ready = true;
    cv.notify_one();
  }
};

TEST_F(WebServerTest, Connecting_is_correct) {
  givenPortAndMessage("9090", "");
  whenServerIsAcceptingConnection();
  thenSocketShouldBeOpen();
}
TEST_F(WebServerTest, Sending_to_server_is_correct) {
  givenPortAndMessage("9090", "Test message!");
  whenServerIsAcceptingConnection();
  whenServerIsAcceptingRequest();
  thenReceivedRequestShouldContainMessage();
}

#endif