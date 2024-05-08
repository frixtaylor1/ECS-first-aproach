/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"
#include "../Entity/Entity.hpp"

#include <unordered_map>
#include <functional>

class CollisionSystem : implements ISystem {
private:
    using CollisionHandler = std::function<void(ScopePtr<Entity>&, ScopePtr<Entity>&)>;
public:
    CollisionSystem(EntityContainer entities);
    ~CollisionSystem();

    void update(ScopePtr<Entity>& entityA);
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