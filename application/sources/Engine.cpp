#include "bm/Engine.hpp"
#include "bm/Logger.hpp"

namespace bm {
    /*static*/ Engine& Engine::GetInstance() {
        static Engine sInstance;
        return sInstance;
    }

    Engine::Engine() = default;

    bool Engine::Initialize() {
        bool Status = true;
        for (auto& [Identifier, SubSystem]: m_SubSystems) {
            if (SubSystem && !SubSystem->Initialize()) {
                Status = false;
            }
        }
        return Status;
    }

    void Engine::Update() {
        for (auto& [Identifier, SubSystem]: m_SubSystems) {
            if (SubSystem) {
                SubSystem->Update();
            }
        }
    }

    void Engine::Deinitialize() {
        for (auto& [Identifier, SubSystem]: m_SubSystems) {
            if (SubSystem) {
                SubSystem->Deinitialize();
            }
        }
    }
}