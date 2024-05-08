/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#include "./CollisionSystem.hpp"

CollisionSystem::CollisionSystem(EntityContainer entities) : m_entities(entities) {}
CollisionSystem::~CollisionSystem() = default;


void CollisionSystem::update(ScopePtr<Entity>& entityA) {
    for (ScopePtr<Entity>& entityB : m_entities) {
        updateCollisionBetween(entityA, entityB);
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
    return entity->getComponent<PlayerComponent>();
}

CollisionComponent* CollisionSystem::isCollisionComponent(ScopePtr<Entity>& entity) {
    return entity->getComponent<CollisionComponent>();
}

RectangleDrawableComponent* CollisionSystem::isRectangleComponent(ScopePtr<Entity>& entity) {
    return entity->getComponent<RectangleDrawableComponent>();
}

/**  
 * MIT License
 *  
 * Copyright (c) 2024 Kevin Daniel Taylor
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */