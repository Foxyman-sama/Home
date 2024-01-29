#include "config.h"

#ifdef Testing

#include "test/tests.hpp"

int main(int argc, char **argv) { return startTests(argc, argv); }

#else

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
    server.handle(socket);
    container.extractToFile();
  }
}

#endif