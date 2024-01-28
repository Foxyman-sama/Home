#ifndef TEST_WEBSERVER_HPP
#define TEST_WEBSERVER_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <format>
#include <future>
#include <memory>

#include "modules/core/controller_impl.hpp"
#include "modules/core/hash_table.hpp"
#include "modules/webserver/webserver.hpp"
#include "utility/generators.hpp"
#include "utility/reader.hpp"

using namespace testing;
using namespace home;
using namespace controller;
using namespace webserver;

class MockController : public Controller {
 public:
  MOCK_METHOD((HashTable<std::string, std::string>), save, (const std::string&), (override));
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

  std::string post(const std::string& body) {
    auto request { makeRequestHeader(net::http::verb::post, "/") };
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
  std::string actual;
  std::string expected;

  WebServerTest() : server { io, 9090, controller } {}

  void thenActualAndExpectedDataShouldBeEqual() { ASSERT_EQ(actual, expected); }
};
class WebServerGetTest : public WebServerTest {
 private:
  std::string target;
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
};
class WebServerPostTest : public WebServerTest {
 private:
  std::string html;
  HashTable<std::string, std::string> return_controller;

 public:
  void givenNumberOfFilesAndMaxFileSize(size_t number_of_files, size_t max_file_size) {
    auto [generated, files] { generateHTMLWithFiles<std::string, std::string>(number_of_files, max_file_size) };
    html = std::get<0>(generated);
    expected += std::format("amount_of_data - {}\n", std::get<2>(generated));
    expected += std::format("number_of_files - {}\n", std::get<1>(generated));
    return_controller.emplace("number_of_files", std::to_string(std::get<1>(generated)));
    return_controller.emplace("amount_of_data", std::to_string(std::get<2>(generated)));
    EXPECT_CALL(controller, save(_)).WillOnce(Return(return_controller));
  }
  void givenExpected(const std::string& expected) { this->expected = expected; }

  void whenClientIsSendingPost() {
    auto wait_connection { std::async(std::launch::async, &TestConnection::connect, &connection) };
    auto socket { server.accept() };
    wait_connection.wait();

    auto wait_posting { std::async(std::launch::async, &TestConnection::post, &connection, html) };
    server.handle(socket);
    actual = wait_posting.get();
  }
};

TEST_F(WebServerGetTest, Correct_request_return_index_html) {
  givenTargetAndExpected("/", readFile("build/index.html"));
  whenClientIsGetting();
  thenActualAndExpectedDataShouldBeEqual();
}
TEST_F(WebServerGetTest, Request_with_bad_target_return_error) {
  givenTargetAndExpected("@", ErrorMessages::bad_target.data());
  whenClientIsGetting();
  thenActualAndExpectedDataShouldBeEqual();
}
TEST_F(WebServerPostTest, Correct_request_return_correct_info_about_files) {
  givenNumberOfFilesAndMaxFileSize(100, 100);
  whenClientIsSendingPost();
  thenActualAndExpectedDataShouldBeEqual();
}
TEST_F(WebServerPostTest, Empty_request_return_error) {
  givenExpected(ErrorMessages::empty_post.data());
  whenClientIsSendingPost();
  thenActualAndExpectedDataShouldBeEqual();
}

#endif