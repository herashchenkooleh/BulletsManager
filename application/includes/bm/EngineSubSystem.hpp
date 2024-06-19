#pragma once

#include <typeindex>

#include "bm/Entity.hpp"

namespace bm {
    class EngineSubSystem {
    public:
        using Identifier = std::size_t;
        using Ptr = std::shared_ptr<EngineSubSystem>;

    public:
        EngineSubSystem();
        virtual ~EngineSubSystem();

        virtual bool Initialize() = 0;
        virtual void Update() = 0;
        virtual void Deinitialize() = 0;

        virtual void RegisterEntity(Entity::Ptr InEntity) = 0;
        virtual void UnregisterEntity(Entity::Ptr InEntity) = 0;

        [[nodiscard]] const Identifier& GetID() const { return m_ID; }

    private:
        Identifier m_ID;
    };
}