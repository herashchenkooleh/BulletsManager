#pragma once

#include <typeindex>
#include <unordered_map>
#include "bm/EngineSubSystem.hpp"

namespace bm {
    class Engine {
    public:
        static Engine& GetInstance();

        Engine(const Engine& InObject) = delete;
        Engine& operator=(const Engine& InObject) = delete;

        bool Initialize();
        void Update();
        void Deinitialize();

        template<typename EngineSubSystemType, typename ...Args>
        typename EngineSubSystemType::Ptr RegisterSubSystem(Args... InArgs) {
            decltype(auto) TypeIndex = std::type_index(typeid(EngineSubSystemType)).hash_code();
            if (auto SubSystem = m_SubSystems.find(TypeIndex); SubSystem != m_SubSystems.end()) {
                return SubSystem->second;
            }
            decltype(auto) NewSubSystem = std::make_shared<EngineSubSystemType>(std::forward<Args>(InArgs)...);
            m_SubSystems[TypeIndex] = NewSubSystem;

            return NewSubSystem;
        }

        template<typename EngineSubSystemType>
        bool UnregisterSubSystem() {
            decltype(auto) TypeIndex = std::type_index(typeid(EngineSubSystemType)).hash_code();
            if (auto SubSystem = m_SubSystems.find(TypeIndex); SubSystem != m_SubSystems.end()) {
                m_SubSystems.erase(TypeIndex);
                return true;
            }

            return false;
        }

    private:
        Engine();

        using SubSystemsMap = std::unordered_map<EngineSubSystem::Identifier, EngineSubSystem::Ptr>;

    private:
        SubSystemsMap m_SubSystems;
    };
}
