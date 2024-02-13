#ifndef TEST_WEBSERVER_HPP
#define TEST_WEBSERVER_HPP

#include "test_base.hpp"

class TestConnection {
 private:
  net::io_context io;
  net::tcp_stream stream;

 public:
  TestConnection() : stream { io } {}
  ~TestConnection() {
    net::error_code ec;
    stream.socket().shutdown(net::tcp::socket::shutdown_both, ec);
  }

  void connect() {
    net::tcp::resolver resolver { io };
    const auto endpoint { resolver.resolve("127.0.0.1", "9090") };
    stream.connect(endpoint);
  }

  std::string get(const std::string &target, const std::string &body) {
    auto request { makeRequestHeader(net::http::verb::get, target) };
    request.content_length(body.size());
    request.body() = body;
    net::http::write(stream, request);

    auto response { read() };
    return response.body();
  }

  std::string post(const std::string &target, const std::string &body) {
    auto request { makeRequestHeader(net::http::verb::post, target) };
    request.content_length(body.size());
    request.body() = body;
    net::http::write(stream, request);

    auto response { read() };
    return response.body();
  }

 private:
  net::http::request<net::http::string_body> makeRequestHeader(net::http::verb verb, const std::string &target) {
    net::http::request<net::http::string_body> request { verb, target, 10 };
    request.set(net::http::field::host, "127.0.0.1");
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

class MockController : public Controller {
 public:
  MOCK_METHOD((std::unordered_map<std::string, std::string>), save, (const std::string &), (override));
};

class WebServerTest : public Test {
 private:
  net::io_context io;
  std::unique_ptr<WebServer> server;
  HTMLContainer container;
  TestConnection connection;
  std::vector<std::tuple<std::string, std::string, net::http::verb>> requests;
  std::vector<std::string> expected;
  std::vector<std::string> actual;

 public:
  MockController controller;

  void SetUp() override {
    container.emplace("/", "build/index.html");
    server.reset(new WebServer { io, 9090, controller, container });
  }

  void appendRequests(std::vector<std::tuple<std::string, std::string, net::http::verb>> range) {
    requests.insert(end(requests), begin(range), end(range));
  }
  void appendExpected(std::vector<std::string> range) { expected.insert(end(expected), begin(range), end(range)); }

  void handle() {
    for_each(requests, [this](const auto &request) {
      const auto wait_connection { std::async(std::launch::async, &TestConnection::connect, &connection) };
      auto socket { server->accept() };
      wait_connection.wait();

      const auto &[target, body, type] { request };
      std::future<std::string> th;
      if (type == net::http::verb::get) {
        th = std::async(std::launch::async, &TestConnection::get, &connection, target, body);
      } else if (type == net::http::verb::post) {
        th = std::async(std::launch::async, &TestConnection::post, &connection, target, body);
      }

      server->handle(socket);
      actual.emplace_back(th.get());
    });
  }

  void assertActualIsEqualExpected() { ASSERT_EQ(actual, expected); }
};

TEST_F(WebServerTest, Get_request_with_default_target_return_index_html) {
  appendRequests({ { "/", "", net::http::verb::get } });
  appendExpected({ readFile(directory + "index.html") });

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WebServerTest, Get_request_with_bad_target_return_error) {
  appendRequests({ { "@", "", net::http::verb::get } });
  appendExpected({ ErrorMessages::bad_target.data() });

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WebServerTest, Empty_post_request_return_error) {
  appendRequests({ { "/", "", net::http::verb::post } });
  appendExpected({ ErrorMessages::empty_post.data() });

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WebServerTest, Post_request_without_files_return_error) {
  appendRequests({ { "/", "f", net::http::verb::post } });
  appendExpected({ ErrorMessages::bad_request.data() });

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WebServerTest, Post_request_with_chrome_boundary_and_file_call_save) {
  const auto post {
    "------WebKitForm\n"
    "filename=\"f\"\n"
    "\r\n"
    "\rf"
    "------WebKitForm\n"
  };
  appendRequests({ { "/", post, net::http::verb::post } });
  appendExpected({ "" });
  EXPECT_CALL(controller, save(_));

  handle();

  assertActualIsEqualExpected();
}
TEST_F(WebServerTest, Post_request_with_firefox_boundary_and_file_call_save) {
  const auto post {
    "-----------------------------n"
    "filename=\"f\"\n"
    "\r\n"
    "\rf"
    "-----------------------------\n"
  };
  appendRequests({ { "/", post, net::http::verb::post } });
  appendExpected({ "" });
  EXPECT_CALL(controller, save(_));

  handle();

  assertActualIsEqualExpected();
}

#endif