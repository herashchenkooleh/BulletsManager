#pragma once

#include "bm/EngineSubSystem.hpp"
#include "bm/Renderer.hpp"

namespace bm {
    class RenderSubSystem : public EngineSubSystem {
    public:
        RenderSubSystem();

        ~RenderSubSystem() override;

        bool Initialize() override;
        void Update() override;
        void Deinitialize() override;

        void RegisterEntity(Entity::Ptr InEntity) override;
        void UnregisterEntity(Entity::Ptr InEntity) override;

    private:
        Renderer::Ptr mRenderer;
    };
}