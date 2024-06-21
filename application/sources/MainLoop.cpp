#include "bm/MainLoop.hpp"
#include "bm/Window.hpp"
#include "bm/Engine.hpp"
#include "GLFW/glfw3.h"
#include "bm/Logger.hpp"
#include "bm/RenderSubSystem.hpp"

namespace bm {
    MainLoop::MainLoop()
        : m_Window(nullptr)
    {

    }

    MainLoop::~MainLoop() = default;

    bool MainLoop::Initialize(const Window::Ptr& InWindow) {
        if (!InWindow) {
            Logger::GetInstance().Fatal("Failed initialize engine: invalid window");
            return false;
        }

        m_Window = InWindow;

        Engine::GetInstance().RegisterSubSystem<RenderSubSystem>(m_Window);

        if (!Engine::GetInstance().Initialize()) {
            Logger::GetInstance().Fatal("Failed initialize engine");
            return false;
        }

        return true;
    }

    void MainLoop::Start() const {
        while (!m_Window->ShouldClose()) {
            glfwPollEvents();
            Engine::GetInstance().Update();
        }
    }

    void MainLoop::Deinitialize() {
        Engine::GetInstance().Deinitialize();
    }
}