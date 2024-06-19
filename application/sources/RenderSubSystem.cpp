#include "bm/RenderSubSystem.hpp"

#include "bm/Configs.hpp"
#include "bm/VulkanRenderer.hpp"
#include "bm/Logger.hpp"

namespace bm {
    RenderSubSystem::RenderSubSystem()
        : mRenderer(nullptr) {
    }

    RenderSubSystem::~RenderSubSystem() /*override*/ = default;

    bool RenderSubSystem::Initialize() /*override*/ {
        if (!mRenderer) {
            decltype(auto) RenderApiName = Configs::GetInstance().Get<std::string>(Configs::sGlobalRenderApiName);
            if (RenderApiName == "vulkan") {
                mRenderer = std::make_shared<VulkanRenderer>();
            } else {
                Logger::GetInstance().Fatal("Unsupported render api: %s", RenderApiName);
                return false;
            }
        }

        if (mRenderer && !mRenderer->IsInitialized()) {
            mRenderer->Initialize();
        }

        bool Status = mRenderer->IsInitialized();
        if (!Status) {
            Logger::GetInstance().Fatal("Failed initialize render subsystem");
        }

        return Status;
    }

    void RenderSubSystem::Update() /*override*/ {
    }

    void RenderSubSystem::Deinitialize() /*override*/ {
    }

    void RenderSubSystem::RegisterEntity(Entity::Ptr InEntity) /*override*/ {

    }

    void RenderSubSystem::UnregisterEntity(Entity::Ptr InEntity) /*override*/ {
    }
}