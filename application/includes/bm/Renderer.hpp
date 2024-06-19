#pragma once

#include <memory>

namespace bm {
    class Renderer {
    public:
        using Ptr = std::shared_ptr<Renderer>;

        Renderer();
        virtual ~Renderer();

        virtual bool Initialize() = 0;
        virtual void Update() = 0;
        virtual void Deinitialize() = 0;

        [[nodiscard]] virtual bool IsInitialized() const = 0;
    };
}