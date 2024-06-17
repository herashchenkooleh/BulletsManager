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
        using Ptr = std::shared_ptr<Window>;

        Window();
        ~Window();


        bool Create(const std::string& InTitle);
        bool ShouldClose() const;

    private:
        ImplementationPtr m_Implementation;
    };
}