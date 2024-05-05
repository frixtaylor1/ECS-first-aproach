/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include "../../Utils/Allocators/StaticVectorAllocator.hpp"
#include "../Component/IComponent.hpp"

#include <cassert>
#include <vector>

#define ENTITY_COMPONENTS_CAPACITY 7

class Entity {
private:
    enum { COMPONENTS_MAX_CAPACITY = ENTITY_COMPONENTS_CAPACITY };
    using ComponentContainer = std::vector<ScopePtr<IComponent, true>, StaticVectorAllocator<ScopePtr<IComponent, true>, COMPONENTS_MAX_CAPACITY> >;
public:
    Entity();
    virtual ~Entity();

    bool operator == (const Entity& entity) const;
    bool operator == (size_t anId) const;
    size_t getId() const;

    template <typename ComponentType>
    ComponentType* getComponent() const noexcept {
        for (const ScopePtr<IComponent, true>& component : m_components) {
            if (ComponentType* castedComponent = dynamic_cast<ComponentType*>(component.get())) {
                return castedComponent;
            }
        }
        return nullptr;
    }

    template <typename ComponentType, typename... Args>
    void addComponent(Args &&...args) {
        assert(m_components.size() < COMPONENTS_MAX_CAPACITY && "Error, [Capacity] of entity component vector exceded!");
        m_components.emplace_back(new ComponentType(std::forward<Args>(args)...));
    }

    void markForRemoval() {
        m_markedForRemoval = true;
    }

    bool isMarkedForRemoval() const {
        return m_markedForRemoval;
    }

private:
    size_t              id;
    static size_t       id_counter;
    ComponentContainer  m_components;
    bool                m_markedForRemoval = false;
};

using EntityContainer = std::vector<ScopePtr<Entity>, StaticVectorAllocator<Entity, 1024>>&;

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