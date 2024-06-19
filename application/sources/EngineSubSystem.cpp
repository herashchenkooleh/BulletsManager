#include "bm/EngineSubSystem.hpp"

#include <typeindex>

namespace bm {
    EngineSubSystem::EngineSubSystem()
        : m_ID(reinterpret_cast<std::size_t>(this))
    {

    }

    /*virtual*/ EngineSubSystem::~EngineSubSystem() = default;

}
