#ifndef LOCALHOST_APP_INCLUDE_HPP
#define LOCALHOST_APP_INCLUDE_HPP

#include <iostream>
#include "server/server.hpp"
#include "ui/ui.hpp"
#include "ui/controller.hpp"

namespace local {
void runApp() {
    std::thread { []() {  
        auto &ui { ui::UI::getUI() };
        ui.init("Server", 800, 600);
        ui.start();
    } }.detach();
    while (true) {
        core::net::io_context io { };
        try {
            auto p_controller { std::make_shared<ui::Controller>() };
            host::Server server { io, 9191, p_controller };
            server.start();
            io.run();
        }
        catch (const std::exception &_k_e) {
            std::cerr << _k_e.what() << '\n';
        }
    }
}
}

#endif
