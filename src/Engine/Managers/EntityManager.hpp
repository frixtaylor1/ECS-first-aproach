/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include "../ECS/Entity/Entity.hpp"
#include <algorithm>

template <size_t MaxCapacity = 1024>
class EntityManager {
private:
    enum { ENTITIES_MAX_CAPACITY = MaxCapacity };
    using Container = std::vector<ScopePtr<Entity, false>, StaticVectorAllocator<Entity, ENTITIES_MAX_CAPACITY>>;
public:

    EntityManager();
    ~EntityManager();

    /**
     * addEntity: adds an entity
     * 
     * @param Entity* entity 
     */
    void addEntity(Entity* entity);

    /**
     * addComponent: adds a component to an entity.
     * 
     * @param size_t entityId
     * @param variadic args
     * 
     * @return nothing.
     */
    template <typename ComponentType, typename... Args>
    void addComponent(size_t entityId, Args &&...args);

    /**
     * addComponent: adds a component to an entity.
     * 
     * @param ScopePtr<Entity>& entity
     * @param variadic args
     * 
     * @return nothing.
     */
    template <typename ComponentType, typename... Args>
    void addComponent(ScopePtr<Entity>& entity, Args &&...args);

    /**
     * removeEntity: this member function mark an entity to be removed.
     * The entity is not removed till the execution of update() function member.
     * 
     * @param size_t entityId
     * 
     * @return nothing.
     */
    void removeEntity(size_t entityId);

    /**
     * removeEntity: this member function mark an entity to be removed.
     * The entity is not removed till the execution of update() function member.
     * 
     * @param ScopePtr<Entity>& entity
     * 
     * @return nothing.
     */
    void removeEntity(const ScopePtr<Entity>& entity);

    /**
     * update: Updates the state of the entity container {m_entities}. 
     */
    void update();

    /** @getters: 
     *  - getLastInsertEntity
     *  - getEntityById
     *  - getEntities
    */

    /**
     * getLastInsertEntity.
     * 
     * @return ScopePtr<Entity>& 
     */
    ScopePtr<Entity>& getLastInsertEntity();
    
    /**
     * getEntityById.
     * 
     * @return ScopePtr<Entity>& 
     */
    ScopePtr<Entity>& getEntityById(size_t id);

    /**
     * getEntities.
     * 
     * @return Container&
     */
    Container& getEntities();

private:
    void removeMarkedEntities();

private:
    Container m_entities{};
};

#include "./EntityManagerImpl.hpp"

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