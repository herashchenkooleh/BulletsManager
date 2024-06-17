#include "bm/MainLoop.hpp"
#include "bm/Window.hpp"
#include "GLFW/glfw3.h"

namespace bm {
    MainLoop::MainLoop()
        : m_Window(nullptr)
    {

    }

    MainLoop::~MainLoop() = default;

    bool MainLoop::Initialize(const Window::Ptr& InWindow) {
        if (!InWindow) {
            return false;
        }

        m_Window = InWindow;

        return true;
    }

    void MainLoop::Start() const {
        while (!m_Window->ShouldClose()) {
            glfwPollEvents();
        }
    }

    void MainLoop::Deinitialize() {

    }
}