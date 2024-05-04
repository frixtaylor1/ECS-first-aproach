#include "./PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(EntityContainer entities) : m_entities(entities) {}
PhysicsSystem::~PhysicsSystem() {}

void PhysicsSystem::update() {
    double currentFrame = GetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    for (ScopePtr<Entity>& entity : m_entities) {
        if (!isPhysicsComponent(entity)) {
            continue;
        }

        if (m_physicsHandlers.find(entity->getId()) != m_physicsHandlers.end()) {
            m_physicsHandlers[entity->getId()](entity, m_deltaTime);
        }
    }
}

void PhysicsSystem::setPhysicsHandler(size_t entityId, PhysicsHandler handler) {
    m_physicsHandlers[entityId] = handler;
}

PhysicsComponent* PhysicsSystem::isPhysicsComponent(ScopePtr<Entity>& entity) {
    return entity->getComponent<PhysicsComponent>();
}