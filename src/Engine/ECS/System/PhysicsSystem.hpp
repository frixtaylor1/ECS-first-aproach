#pragma once

#include "../Entity/Entity.hpp"
#include "./ISystem.hpp"

template <int FramePerSeconds = 60>
class PhysicsSystem : implements ISystem {
public:
    PhysicsSystem(const EntityContainer entities) : m_entities(entities) {}

    void update(float delta = 0.016f) {
        /**
         * @todo: investigar acerca de la lógica física.. 
         */
    }
private:

    EntityContainer m_entities;
};