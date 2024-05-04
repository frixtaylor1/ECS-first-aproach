#pragma once

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"

#include <unordered_map>
#include <functional>

class PhysicsSystem : implements ISystem {
private:
    using PhysicsHandler = std::function<void(ScopePtr<Entity>&, float delta)>;
public:
    PhysicsSystem(EntityContainer entities);
    virtual ~PhysicsSystem();

    void update();
    void setPhysicsHandler(size_t entityId, PhysicsHandler handler);

private:
    PhysicsComponent* isPhysicsComponent(ScopePtr<Entity>& entity);

private:
    double          m_lastFrame = GetTime();
    double          m_deltaTime = 0;
    EntityContainer m_entities;
    std::unordered_map<int, PhysicsHandler> m_physicsHandlers;
};