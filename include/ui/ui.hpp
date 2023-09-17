#ifndef LOCALHOST_UI_INCLUDE_HPP
#define LOCALHOST_UI_INCLUDE_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "displayed_connection.hpp"
#include "status.hpp"
#include "core.hpp"

namespace local::ui {
class UI {
private:
    GLFWwindow *p_win_;
    const char *pk_wtitle_;
    int wwidth_;
    int wheight_;
    std::vector<DisplayedConnection> connections_;

    UI() noexcept;
    ~UI() noexcept;
    void draw() noexcept;

public:
    static UI &getUI() noexcept;
    void init(const char *_pk_windows_title, int _wwidth, int _wheight);
    void start();
    void addSessionToUI(DisplayedConnection &&_conn) noexcept;
    void deleteSessionFromUI(core::Size _id) noexcept;
    void changeSessionStatus(core::Size _id, 
                             const std::string &_k_status) noexcept;
};
}

#endif
