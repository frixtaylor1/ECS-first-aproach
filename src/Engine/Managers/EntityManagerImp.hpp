#ifndef ENTITY_MANAGER_IMPL_HPP
#define ENTITY_MANAGER_IMPL_HPP

#include "EntityManager.hpp"

template <size_t MaxCapcity>
EntityManager<MaxCapcity>::EntityManager() = default;

template <size_t MaxCapcity>
void EntityManager<MaxCapcity>::addEntity(Entity* entity) {
    m_entities.emplace_back(entity);
}

template <size_t MaxCapcity>
template <typename ComponentType, typename... Args>
void EntityManager<MaxCapcity>::addComponent(size_t entityId, Args &&...args) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (*entity == entityId) {
            entity->addComponent<ComponentType>(std::forward<Args>(args)...);
            return;
        }
    }
}

template <size_t MaxCapcity>
template <typename ComponentType, typename... Args>
void EntityManager<MaxCapcity>::addComponent(ScopePtr<Entity>& entity, Args &&...args) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (*entity == *entity) {
            entity->addComponent<ComponentType>(std::forward<Args>(args)...);
        }
    }
}

template <size_t MaxCapcity>
void EntityManager<MaxCapcity>::removeEntity(size_t entityId) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (entity->getId() == entityId) {
            entity->markForRemoval();
            break;
        }
    }
}

template <size_t MaxCapcity>
void EntityManager<MaxCapcity>::removeMarkedEntities() {
    auto it = std::remove_if(m_entities.begin(), m_entities.end(),
        [](const ScopePtr<Entity>& entity) {
            return entity->isMarkedForRemoval();
        });
    m_entities.erase(it, m_entities.end());
}

template <size_t MaxCapcity>
ScopePtr<Entity>& EntityManager<MaxCapcity>::getLastInsertEntity() {
    return m_entities.back();
}

template <size_t MaxCapcity>
ScopePtr<Entity>& EntityManager<MaxCapcity>::getEntityById(size_t id) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return m_entities.end();
}

template <size_t MaxCapcity>
typename EntityManager<MaxCapcity>::Container& EntityManager<MaxCapcity>::getEntities() {
    return m_entities;
}

#endif // ENTITY_MANAGER_IMPL_HPP
