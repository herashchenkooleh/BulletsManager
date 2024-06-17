#pragma once

#include "bm/Window.hpp"

namespace bm {
    class MainLoop {
    public:
        using Ptr = std::shared_ptr<MainLoop>;

        MainLoop();
        ~MainLoop();

        bool Initialize(const Window::Ptr& InWindow);
        void Start() const;
        void Deinitialize();
    private:
        Window::Ptr m_Window;
    };
}
