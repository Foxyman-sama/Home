#include "config.h"

#ifdef Testing

#include "test/tests.hpp"

int main(int argc, char **argv) { return startTests(argc, argv); }

#else

#include <format>
#include <iostream>

#include "modules/core/controller_impl.hpp"
#include "modules/core/interactor_impl.hpp"
#include "modules/webserver/html_parser.hpp"
#include "modules/webserver/webserver.hpp"

int main(int _argc, char **_p_argv) {
  net::io_context io;
  home::container::JSONContainer container { "data.json" };
  home::interactor::InteractorImpl interactor { container };
  home::webserver::HTMLParser parser;
  home::controller::ControllerImpl controller { interactor, parser };
  home::webserver::HTMLContainer htmls;
  htmls.emplace("/", "build/index.html");

  home::webserver::WebServer server { io, 9090, controller, htmls };
  while (true) {
    auto socket { server.accept() };
    while (true) {
      try {
        server.handle(socket);
      } catch (...) {
        std::cerr << std::format("{} is dropped\n", socket.remote_endpoint().address().to_string());
        break;
      }
    }

    net::error_code ec;
    socket.shutdown(net::tcp::socket::shutdown_both, ec);
    container.extractToFile();
  }
}

#endif