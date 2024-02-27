#include "config.h"

#ifdef Testing

#include "test/tests.hpp"

bool isExisted(std::string path) {
  std::ifstream fin { path };
  return fin.is_open();
}
void makeHTML(std::string output, std::string boundary, std::vector<std::string> filenames) {
  HTMLMaker maker { boundary };
  for_each(filenames, [&](const auto &filename) { maker.appendFile(filename, readFile(directory + filename)); });

  auto [html, _, __] { maker.getFileGeneratedParamsAndIfNotEmptyAddLastBounary() };
  std::ofstream fout { output, std::ios_base::binary };
  fout.write(html.data(), html.size());
}

int main(int argc, char **argv) {
  if (isExisted("build/test_chrome.html") == false) {
    makeHTML("build/test_chrome.html", Delims::chrome_boundary.data(),
             { "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });
  }
  if (isExisted("build/test_firefox.html") == false) {
    makeHTML("build/test_firefox.html", Delims::firefox_boundary.data(),
             { "1.pdf", "1.png", "2.png", "12.pdf", "13.pdf", "14.pdf" });
  }

  return startTests(argc, argv);
}

#else

#include <format>
#include <iostream>

#include "modules/core/controller_impl.hpp"
#include "modules/core/interactor_impl.hpp"
#include "modules/core/json_container.hpp"
#include "modules/webserver/html_parser.hpp"
#include "modules/webserver/webserver.hpp"

int main() {
  net::io_context io;
  home::container::JSONContainer container { "build/data.json" };
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