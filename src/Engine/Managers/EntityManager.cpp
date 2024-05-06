/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#include "EntityManager.hpp"

#include "EntityManager.hpp"

EntityManager::EntityManager() = default;

EntityManager::~EntityManager() = default;

void EntityManager::addEntity(Entity* entity) {
    m_entities.emplace_back(entity);
}

void EntityManager::removeEntity(size_t entityId) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (entity->getId() == entityId) {
            entity->markForRemoval();
            break;
        }
    }
}

void EntityManager::removeEntity(const ScopePtr<Entity>& entity) {
    removeEntity(entity->getId());
}


void EntityManager::update() {
    removeMarkedEntities();
}

void EntityManager::removeMarkedEntities() {
    auto it = std::remove_if(m_entities.begin(), m_entities.end(),
        [](const ScopePtr<Entity>& entity) {
            return entity->isMarkedForRemoval();
        });
    m_entities.erase(it, m_entities.end());
}


ScopePtr<Entity>& EntityManager::getLastInsertEntity() {
    return m_entities.back();
}

ScopePtr<Entity>& EntityManager::getEntityById(size_t id) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return m_entities.back();
}

typename EntityManager::Container& EntityManager::getEntities() {
    return m_entities;
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