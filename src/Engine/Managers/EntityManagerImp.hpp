#ifndef ENTITY_MANAGER_IMPL_HPP
#define ENTITY_MANAGER_IMPL_HPP

#include "EntityManager.hpp"

template <size_t MaxCapacity>
EntityManager<MaxCapacity>::EntityManager() = default;

template <size_t MaxCapacity>
EntityManager<MaxCapacity>::~EntityManager() = default;

template <size_t MaxCapacity>
void EntityManager<MaxCapacity>::addEntity(Entity* entity) {
    m_entities.emplace_back(entity);
}

template <size_t MaxCapacity>
template <typename ComponentType, typename... Args>
void EntityManager<MaxCapacity>::addComponent(size_t entityId, Args &&...args) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (*entity == entityId) {
            entity->addComponent<ComponentType>(std::forward<Args>(args)...);
            return;
        }
    }
}

template <size_t MaxCapacity>
template <typename ComponentType, typename... Args>
void EntityManager<MaxCapacity>::addComponent(ScopePtr<Entity>& entity, Args &&...args) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (*entity == *entity) {
            entity->addComponent<ComponentType>(std::forward<Args>(args)...);
        }
    }
}

template <size_t MaxCapacity>
void EntityManager<MaxCapacity>::removeEntity(size_t entityId) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (entity->getId() == entityId) {
            entity->markForRemoval();
            break;
        }
    }
}

template <size_t MaxCapacity>
void EntityManager<MaxCapacity>::update() {
    removeMarkedEntities();
}

template <size_t MaxCapacity>
void EntityManager<MaxCapacity>::removeMarkedEntities() {
    auto it = std::remove_if(m_entities.begin(), m_entities.end(),
        [](const ScopePtr<Entity>& entity) {
            return entity->isMarkedForRemoval();
        });
    m_entities.erase(it, m_entities.end());
}

template <size_t MaxCapacity>
ScopePtr<Entity>& EntityManager<MaxCapacity>::getLastInsertEntity() {
    return m_entities.back();
}

template <size_t MaxCapacity>
ScopePtr<Entity>& EntityManager<MaxCapacity>::getEntityById(size_t id) {
    for (ScopePtr<Entity>& entity : m_entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return m_entities.end();
}

template <size_t MaxCapacity>
typename EntityManager<MaxCapacity>::Container& EntityManager<MaxCapacity>::getEntities() {
    return m_entities;
}

#endif // ENTITY_MANAGER_IMPL_HPP
