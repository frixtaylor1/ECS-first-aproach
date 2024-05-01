#pragma once

#include "../../Allocators/StaticAllocator.hpp"
#include "../Component/IComponent.hpp"

#include <cassert>
#include <vector>

class Entity {
public:
    Entity() = default;

    virtual ~Entity() {
    }

    template <typename ComponentType>
    ComponentType* getComponent() const noexcept {
        for (const auto& component : m_components) {
            if (auto castedComponent = dynamic_cast<ComponentType*> (component.get())) {
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
    enum { COMPONENTS_MAX_CAPACITY = 5 };
    std::vector<ScopePtr<IComponent>, StaticAllocator<ScopePtr<IComponent>, COMPONENTS_MAX_CAPACITY> > m_components;
};