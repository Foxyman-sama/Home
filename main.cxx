#include "config.h"

#ifdef Testing

#include "test/tests.hpp"

int main(int argc, char **argv) { return startTests(argc, argv); }

#else

#include <iostream>

#include "modules/core/controller_impl.hpp"
#include "modules/core/interactor_impl.hpp"
#include "modules/webserver/htmlparser.hpp"
#include "modules/webserver/webserver.hpp"

int main(int _argc, char **_p_argv) {
  home::webserver::net::io_context io;
  home::container::JSONContainer container { "data.json" };
  home::interactor::InteractorImpl interactor { container };
  home::webserver::HTMLParser parser;
  home::controller::ControllerImpl controller { interactor, parser };
  home::webserver::WebServer server { io, 9090, controller };
  while (true) {
    auto socket { server.accept() };
    while (true) {
      try {
        server.handle(socket);
      } catch (...) {
        std::cerr << "Dropped\n";
        break;
      }
    }

    home::webserver::net::error_code ec;
    socket.shutdown(home::webserver::net::tcp::socket::shutdown_both, ec);
    container.extractToFile();
  }
}

#endif