#pragma once

#include "../ECS/Entity/Entity.hpp"

template <size_t MaxCapcity = 1024>
class EntityManager {
private:
    enum { ENTITIES_MAX_CAPACITY = MaxCapcity };
    using EntityContainer = std::vector<ScopePtr<Entity>, StaticAllocator<Entity, ENTITIES_MAX_CAPACITY>>;

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

    ScopePtr<Entity>& getLastInsertEntity() {
        return m_entities.back();
    }

    ScopePtr<Entity>& getEntityById(size_t id) {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (*entity == id) {
                return entity;
            }
        }
        m_entities.back();
    }

    EntityContainer& getEntities() {
        return m_entities;
    }

private:
    EntityContainer m_entities{};
};