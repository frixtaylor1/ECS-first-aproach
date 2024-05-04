#pragma once

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"
#include "./InputSystem.hpp"

class PhysicsSystem : implements ISystem {
public:
    PhysicsSystem(const EntityContainer entities);
    virtual ~PhysicsSystem();

    void update();
private:
    void updatePlayer(ScopePtr<Entity>& entity, float delta);
    void updateEnemy(ScopePtr<Entity>& enemy, float delta);

    RectangleDrawableComponent* isDrawableComponent(ScopePtr<Entity>& entity);
    InputComponent*             isInputComponent(ScopePtr<Entity>& entity);
    PhysicsComponent*           isPhysicsComponent(ScopePtr<Entity>& entity);
    CollisionComponent*         isCollisionComponent(ScopePtr<Entity>& entity);
    PlayerComponent*            isPlayerEntity(ScopePtr<Entity>& entity);

    float calculateDeltaY(PhysicsComponent* component, float delta);
    float calculateDeltaX(PhysicsComponent* component, float delta);

private:
    double          m_lastFrame = GetTime();
    EntityContainer m_entities;
};