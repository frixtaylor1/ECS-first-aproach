#pragma once

#include "../ECS/Entity/Entity.hpp"
#include <algorithm>

template <size_t MaxCapcity = 1024>
class EntityManager {
private:
    enum { ENTITIES_MAX_CAPACITY = MaxCapcity };
    using Container = std::vector<ScopePtr<Entity, false>, StaticVectorAllocator<Entity, ENTITIES_MAX_CAPACITY>>;
public:

    EntityManager();

    void addEntity(Entity* entity);
    template <typename ComponentType, typename... Args>
    void addComponent(size_t entityId, Args &&...args);
    template <typename ComponentType, typename... Args>
    void addComponent(ScopePtr<Entity>& entity, Args &&...args);

    void removeEntity(size_t entityId);
    void removeMarkedEntities();

    ScopePtr<Entity>&   getLastInsertEntity();
    ScopePtr<Entity>&   getEntityById(size_t id);
    Container&          getEntities();

private:
    Container m_entities{};
};

#include "./EntityManagerImp.hpp"