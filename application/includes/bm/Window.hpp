#pragma once

#include <memory>
#include <string>

namespace bm
{
    class Window
    {
        struct Implementation;
        using ImplementationPtr = std::shared_ptr<Implementation>;

    public:
        using RenderTargetHandle = void*;
        using Ptr = std::shared_ptr<Window>;

        Window();
        ~Window();

        bool Create(const std::string& InTitle);
        void Destroy();

        bool ShouldClose() const;

        [[nodiscard]] RenderTargetHandle GetRenderTargetHandle() const;

    private:
        ImplementationPtr m_Implementation;
    };
}