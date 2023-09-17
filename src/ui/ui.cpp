#include "ui/ui.hpp"

namespace local::ui {
UI::UI() noexcept 
    : p_win_ { nullptr }, pk_wtitle_ { }, wwidth_ { }, wheight_ { } { }
UI::~UI() noexcept { 
    if (p_win_ != nullptr) {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(p_win_);
        glfwTerminate();
    }
}
void UI::draw() noexcept {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Connections");
    for (auto &&el: connections_) {
        ImGui::Text(el.address_.c_str());
        ImGui::SameLine();
        ImGui::Text(el.port_.c_str());
        ImGui::SameLine();
        ImGui::Text(el.status_.c_str());
    }

    ImGui::End();
}
UI &UI::getUI() noexcept {
    static UI s_ui { };
    return s_ui;
}
void UI::init(const char *_pk_windows_title, int _wwidth, int _wheight) {
    pk_wtitle_ = _pk_windows_title;
    wwidth_ = _wwidth;
    wheight_ = _wheight;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInit();
    p_win_ = glfwCreateWindow(wwidth_, wheight_, pk_wtitle_, nullptr, nullptr);
    glfwMakeContextCurrent(p_win_);
    glfwSwapInterval(1);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(p_win_, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}
void UI::start() {
    while (!glfwWindowShouldClose(p_win_)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        draw();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int win_width { };
        int win_height { };
        glfwGetFramebufferSize(p_win_, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height);
        glfwSwapBuffers(p_win_);
    }
}
void UI::addSessionToUI(DisplayedConnection &&_conn) noexcept {
    connections_.emplace_back(std::move(_conn));
}
void UI::deleteSessionFromUI(core::Size _id) noexcept { 
    auto it { connections_.begin() };
    for (; it != connections_.end(); ++it) {
        if (it->id_ == _id) {
            connections_.erase(it);
            return;
        }
    }
}
void UI::changeSessionStatus(core::Size _id,
                             const std::string &_k_status) noexcept {
    auto it { connections_.begin() };
    for (; it != connections_.end(); ++it) {
        if (it->id_ == _id) {
            it->status_ = std::move(_k_status);
            return;
        }
    }
}
}