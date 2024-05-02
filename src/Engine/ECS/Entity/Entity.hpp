#pragma once

#include "../../Utils/Allocators/StaticAllocator.hpp"
#include "../Component/IComponent.hpp"

#include <cassert>
#include <vector>

#define ENTITY_COMPONENTS_CAPACITY 7

class Entity {
private:
    enum { COMPONENTS_MAX_CAPACITY = ENTITY_COMPONENTS_CAPACITY };
    using ComponentContainer = std::vector<ScopePtr<IComponent>, StaticAllocator<ScopePtr<IComponent>, COMPONENTS_MAX_CAPACITY> >;
public:
    Entity();
    virtual ~Entity();

    bool operator == (const Entity& entity) const;
    bool operator == (size_t anId) const;
    size_t getId() const;

    template <typename ComponentType>
    ComponentType* getComponent() const noexcept {
        for (const ScopePtr<IComponent>& component : m_components) {
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

private:
    size_t              id;
    static size_t       id_counter;
    ComponentContainer  m_components;
};

using EntityContainer = std::vector<ScopePtr<Entity>, StaticAllocator<Entity, 1024> >&;