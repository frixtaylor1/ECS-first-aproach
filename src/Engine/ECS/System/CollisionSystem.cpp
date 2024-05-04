#include "./CollisionSystem.hpp"

CollisionSystem::CollisionSystem(EntityContainer entities) : m_entities(entities) {}
CollisionSystem::~CollisionSystem() {}


void CollisionSystem::update() {
    for (ScopePtr<Entity>& entityA : m_entities) {
        if (!isCollisionComponent(entityA)) {
            continue;
        }

        for (ScopePtr<Entity>& entityB : m_entities) {
            updateCollisionBetween(entityA, entityB);
        }
    }
}

void CollisionSystem::setCollisionHandler(size_t entityId1, size_t entityId2, CollisionHandler handler) {
    size_t key = entityId1 * 1000 + entityId2;
    m_collisionHandlers[key] = handler;
}

void CollisionSystem::updateCollisionBetween(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB) {
    if (*entityA == *entityB) {
        return;
    }

    CollisionComponent* collisionComponentA = isCollisionComponent(entityA);
    CollisionComponent* collisionComponentB = isCollisionComponent(entityB);
    RectangleDrawableComponent* rectangleEntityA = isRectangleComponent(entityA);
    RectangleDrawableComponent* rectangleEntityB = isRectangleComponent(entityB);

    if (!collisionComponentB || !rectangleEntityA || !rectangleEntityB) {
        return;
    }

    if (CheckCollisionRecs(rectangleEntityA->rectangle, rectangleEntityB->rectangle)) {
        collisionComponentA->colliding = true;
        collisionComponentB->colliding = true;

    }
    else {
        collisionComponentA->colliding = false;
        collisionComponentB->colliding = false;
    }

    handleCollision(entityA, entityB);
}

void CollisionSystem::handleCollision(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB) {
    size_t idEntityA = entityA.get()->getId();
    size_t idEntityB = entityB.get()->getId();
    size_t key = idEntityA * 1000 + idEntityB;
    if (m_collisionHandlers.find(key) != m_collisionHandlers.end()) {
        m_collisionHandlers[key](entityA, entityB);
    }
}

PlayerComponent* CollisionSystem::isPlayerComponent(ScopePtr<Entity>& entity) {
    return &*entity->getComponent<PlayerComponent>();
}

CollisionComponent* CollisionSystem::isCollisionComponent(ScopePtr<Entity>& entity) {
    return &*entity->getComponent<CollisionComponent>();
}

RectangleDrawableComponent* CollisionSystem::isRectangleComponent(ScopePtr<Entity>& entity) {
    return &*entity->getComponent<RectangleDrawableComponent>();
}

