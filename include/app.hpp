#ifndef LOCALHOST_APP_INCLUDE_HPP
#define LOCALHOST_APP_INCLUDE_HPP

#include <iostream>
#include "server/server.hpp"

namespace local {
void runApp() {
    host::Server server { 9191 };
    while (true) {
        try {
            server.init();
            core::g_io_context.run();
        }
        catch (const std::exception &_k_e) {
            std::cerr << _k_e.what() << '\n';
            core::g_io_context.reset();
        }
    }
}
}

#endif
