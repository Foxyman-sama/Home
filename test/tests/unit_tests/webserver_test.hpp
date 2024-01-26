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
  net::tcp::acceptor acceptor;
  Controller& controller;

 public:
  WebServer(net::io_context& io, unsigned short port, Controller& controller)
      : acceptor { io, net::tcp::endpoint { net::tcp::v4(), port } }, controller { controller } {}

  net::tcp::socket accept() { return acceptor.accept(); }

  void handle(auto& socket) {
    auto request { receive(socket) };
    if (isGetRequestAndIndexTarget(request)) {
      sendIndexHTML(socket);
    } else if (isPostRequest(request)) {
      processAndSendAnswer(socket, request);
    }
  }

 private:
  bool isGetRequestAndIndexTarget(const auto& request) const noexcept {
    return (request.method() == net::http::verb::get) && (request.target() == "/");
  }
  bool isPostRequest(const auto& request) const noexcept { return request.method() == net::http::verb::post; }

  net::http::request<net::http::string_body> receive(net::tcp::socket& socket) {
    net::flat_buffer buffer;
    net::http::request<net::http::string_body> req;
    net::http::read(socket, buffer, req);
    return req;
  }

  void sendIndexHTML(auto& socket) {
    auto response { createResponseWithIndexHTML() };
    net::http::write(socket, response);
  }
  net::http::response<net::http::file_body> createResponseWithIndexHTML() {
    auto index_html { readFile("build/index.html") };
    return makeResponseWithHTMLFile(index_html);
  }
  net::http::file_body::value_type readFile(const auto& filename) {
    net::http::file_body::value_type file;
    net::error_code ec;
    file.open(filename, net::file_mode::scan, ec);
    return file;
  }
  net::http::response<net::http::file_body> makeResponseWithHTMLFile(auto& file) {
    net::http::response<net::http::file_body> response { std::piecewise_construct, std::make_tuple(std::move(file)),
                                                         std::make_tuple(net::http::status::ok, 10) };
    response.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(net::http::field::content_type, "text/html");
    response.content_length(file.size());
    return response;
  }

  void processAndSendAnswer(auto& socket, const auto& request) {
    auto result { controller.save(request.body()) };
    auto response { makeResponseWithHashTable(result) };
    net::http::write(socket, response);
  }
  net::http::response<net::http::string_body> makeResponseWithHashTable(
      const HashTable<std::string, std::string>& hash_table) {
    net::http::response<net::http::string_body> response { net::http::status::ok, 10 };
    response.set(net::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(net::http::field::content_type, "text/plain");
    for (auto&& [key, value] : hash_table) {
      auto formated { std::format("{} - {}", key, value) };
      response.body() += formated;
      response.content_length(response.body().size() + formated.size());
    }

    return response;
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

    void get(std::string& actual) {
      std::thread { [&, this] { handle(net::http::verb::get, actual); } }.detach();
    }

    void post(std::string& actual, std::string html) {
      std::thread { [&, this] { handle(net::http::verb::post, actual, html); } }.detach();
    }

   private:
    void handle(net::http::verb verb, std::string& actual, std::string html = "") {
      auto request { makeRequest(verb, html) };
      sendRequest(request);

      auto response { receiveResponse() };
      actual = response.body();
    }
    void sendRequest(auto&& request) noexcept {
      net::error_code ec;
      net::http::write(stream, std::move(request), ec);
    }
    net::http::request<net::http::string_body> makeRequest(net::http::verb verb,
                                                           const std::string& body = "") const noexcept {
      net::http::request<net::http::string_body> request { verb, "/", 10 };
      request.set(net::http::field::host, ip);
      request.set(net::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
      request.set(net::http::field::content_length, std::to_string(body.size()));
      request.body() = body;
      return request;
    }
    net::http::response<net::http::string_body> receiveResponse() {
      net::flat_buffer buffer;
      net::http::response<net::http::string_body> response;
      net::http::read(stream, buffer, response);
      return response;
    }
  };

  net::io_context io;
  std::unique_ptr<WebServer> server;
  std::unique_ptr<TestConnection> connection;
  std::string actual;
  std::string expected;
  std::string target;
  Reader reader;
  MockController controller;

 public:
  void givenExpectedHTMLFile(const std::string& filename) {
    server.reset(new WebServer { io, 9090, controller });
    connection.reset(new TestConnection { "127.0.0.1", "9090" });
    reader.open("build/", filename);
    expected = reader.createStreamAndReadFile(filename);
  }

  void whenClientIsSendingGet() {
    connection->connect();

    auto socket { server->accept() };
    connection->get(actual);
    server->handle(socket);
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
  void whenClientIsSendingPost() {
    auto [generated, _] { generateHTMLWithFiles<std::string, std::string>(10, 1'000) };
    auto html { std::get<0>(generated) };
    auto number_of_files { std::get<1>(generated) };
    auto amount_of_data { std::get<2>(generated) };
    auto hash_table { HashTable<std::string, std::string> {
        { title_number_of_files.data(), std::to_string(number_of_files) },
        { title_amount_of_data.data(), std::to_string(amount_of_data) } } };
    EXPECT_CALL(controller, save(html)).WillOnce(Return(hash_table));
    for (auto&& [key, value] : hash_table) {
      auto formated { std::format("{} - {}", key, value) };
      expected += formated;
    }

    connection->connect();

    auto socket { server->accept() };
    connection->get(actual);
    server->handle(socket);
    connection->post(actual, html);
    server->handle(socket);
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }

  void thenActualShouldBeEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(WebServerTest, Get_request_return_index_html) {
  givenExpectedHTMLFile("index.html");
  whenClientIsSendingGet();
  thenActualShouldBeEqualExpected();
}
TEST_F(WebServerTest, Send_post_request_return_accept_html) {
  givenExpectedHTMLFile("/");
  whenClientIsSendingPost();
  thenActualShouldBeEqualExpected();
}

#endif