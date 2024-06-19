#pragma once

#include <memory>

namespace bm {
    class Entity {
    public:
        using Ptr = std::shared_ptr<Entity>;

        Entity();
        virtual ~Entity();
    };
}