/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#include "./PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(EntityContainer entities) : m_entities(entities) {}
PhysicsSystem::~PhysicsSystem() {}

void PhysicsSystem::update() {
    double currentFrame = GetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    for (ScopePtr<Entity>& entity : m_entities) {
        if (!isPhysicsComponent(entity)) {
            continue;
        }

        if (m_physicsHandlers.find(entity->getId()) != m_physicsHandlers.end()) {
            m_physicsHandlers[entity->getId()](entity, m_deltaTime);
        }
    }
}

void PhysicsSystem::setPhysicsHandler(size_t entityId, PhysicsHandler handler) {
    m_physicsHandlers[entityId] = handler;
}

PhysicsComponent* PhysicsSystem::isPhysicsComponent(ScopePtr<Entity>& entity) {
    return entity->getComponent<PhysicsComponent>();
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