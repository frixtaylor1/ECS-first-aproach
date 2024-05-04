#pragma once

#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"
#include "../Entity/Entity.hpp"

#include <unordered_map>
#include <functional>

class CollisionSystem {
private:
    using CollisionHandler = std::function<void(ScopePtr<Entity>&, ScopePtr<Entity>&)>;
public:
    CollisionSystem(EntityContainer entities);
    ~CollisionSystem();

    void update();
    void setCollisionHandler(size_t entityId1, size_t entityId2, CollisionHandler handler);

private:
    void updateCollisionBetween(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB);
    void handleCollision(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB);

    PlayerComponent*            isPlayerComponent(ScopePtr<Entity>& entity);
    CollisionComponent*         isCollisionComponent(ScopePtr<Entity>& entity);
    RectangleDrawableComponent* isRectangleComponent(ScopePtr<Entity>& entity);

private:
    std::unordered_map<int, CollisionHandler> m_collisionHandlers;
    EntityContainer m_entities;
};
