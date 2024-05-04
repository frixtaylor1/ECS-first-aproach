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