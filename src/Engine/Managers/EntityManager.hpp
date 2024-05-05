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

#include "./EntityManagerImp.hpp"