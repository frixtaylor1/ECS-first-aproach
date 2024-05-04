#pragma once

#include "../ECS/Entity/Entity.hpp"
#include <algorithm>

template <size_t MaxCapcity = 1024>
class EntityManager {
private:
    enum { ENTITIES_MAX_CAPACITY = MaxCapcity };
    using Container = std::vector<ScopePtr<Entity, false>, StaticVectorAllocator<Entity, ENTITIES_MAX_CAPACITY>>;
public:

    EntityManager() = default;

    void addEntity(Entity* entity) {
        m_entities.emplace_back(entity);
    }

    template <typename ComponentType, typename... Args>
    void addComponent(size_t entityId, Args &&...args) {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (*entity == entityId) {
                entity->addComponent<ComponentType>(std::forward<Args>(args)...);
                return;
            }
        }
    }

    template <typename ComponentType, typename... Args>
    void addComponent(ScopePtr<Entity>& entity, Args &&...args) {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (*entity == *entity) {
                entity->addComponent<ComponentType>(std::forward<Args>(args)...);
            }
        }
    }

    void removeEntity(size_t entityId) {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (entity->getId() == entityId) {
                entity->markForRemoval();
                break;
            }
        }
    }

    void removeMarkedEntities() {
        auto it = std::remove_if(m_entities.begin(), m_entities.end(),
            [](const ScopePtr<Entity>& entity) {
                return entity->isMarkedForRemoval();
            });
        m_entities.erase(it, m_entities.end());
    }

    ScopePtr<Entity>& getLastInsertEntity() {
        return m_entities.back();
    }

    ScopePtr<Entity>& getEntityById(size_t id) {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (entity->getId() == id) {
                return entity;
            }
        }
        return m_entities.end();
    }

    Container& getEntities() {
        return m_entities;
    }

private:
    Container m_entities{};
};