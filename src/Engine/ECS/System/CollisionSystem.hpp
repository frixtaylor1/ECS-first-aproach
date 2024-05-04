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
    CollisionSystem(EntityContainer entities) : m_entities(entities) {}
    ~CollisionSystem() {}


    void update() {
        for (ScopePtr<Entity>& entityA : m_entities) {
            if (!isCollisionComponent(entityA)) {
                continue;
            }

            for (ScopePtr<Entity>& entityB : m_entities) {
                updateCollisionBetween(entityA, entityB);
            }
        }
    }

    void setCollisionHandler(size_t entityId1, size_t entityId2, CollisionHandler handler) {
        size_t key = entityId1 * 1000 + entityId2;
        m_collisionHandlers[key] = handler;
    }

private:
    void updateCollisionBetween(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB) {
        if (*entityA == *entityB) {
            return;
        }

        CollisionComponent*         collisionComponentA = isCollisionComponent(entityA);
        CollisionComponent*         collisionComponentB = isCollisionComponent(entityB);
        RectangleDrawableComponent* rectangleEntityA    = isRectangleComponent(entityA);
        RectangleDrawableComponent* rectangleEntityB    = isRectangleComponent(entityB);

        if (!collisionComponentB || !rectangleEntityA || !rectangleEntityB) {
            return;
        }

        if (CheckCollisionRecs(rectangleEntityA->rectangle, rectangleEntityB->rectangle)) {
            collisionComponentA->colliding  = true;
            collisionComponentB->colliding  = true;

        } else {
            collisionComponentA->colliding  = false;
            collisionComponentB->colliding  = false;
        }

        handleCollision(entityA, entityB);
    }

    void handleCollision(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB) {
        size_t idEntityA    = entityA.get()->getId();
        size_t idEntityB    = entityB.get()->getId();
        size_t key          = idEntityA * 1000 + idEntityB;
        if (m_collisionHandlers.find(key) != m_collisionHandlers.end()) {
            m_collisionHandlers[key](entityA, entityB);
        }
    }

    PlayerComponent* isPlayerComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<PlayerComponent>();
    }

    CollisionComponent* isCollisionComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<CollisionComponent>();
    }

    RectangleDrawableComponent* isRectangleComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<RectangleDrawableComponent>();
    }

private:
    std::unordered_map<int, CollisionHandler> m_collisionHandlers;
    EntityContainer m_entities;
};
