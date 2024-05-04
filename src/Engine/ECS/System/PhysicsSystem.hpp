#pragma once

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"
#include "./InputSystem.hpp"

class PhysicsSystem : implements ISystem {
public:
    PhysicsSystem(const EntityContainer entities) : m_entities(entities) {}

    void update() {
        double currentFrame = GetTime();
        float  deltaTime    = currentFrame - m_lastFrame;
        m_lastFrame         = currentFrame;

        for (ScopePtr<Entity>& entity : m_entities) {
            updatePlayer(entity, deltaTime);
            /* updateEnemy(entity, deltaTime); */
        }
    }
private:
    void updatePlayer(ScopePtr<Entity>& entity, float delta)
    {
        if (!isPlayerEntity(entity)) {
            return ;
        }

        InputComponent*             inputComponentPlayer      = isInputComponent(entity);
        PhysicsComponent*           physicsComponentPlayer    = isPhysicsComponent(entity);
        RectangleDrawableComponent* drawableComponentPlayer   = isDrawableComponent(entity);

        if (inputComponentPlayer->keyPressed) {
            if (inputComponentPlayer->key == KEY_UP)    drawableComponentPlayer->rectangle.y -= calculateDeltaY(physicsComponentPlayer, delta);
            if (inputComponentPlayer->key == KEY_DOWN)  drawableComponentPlayer->rectangle.y += calculateDeltaY(physicsComponentPlayer, delta);
            if (inputComponentPlayer->key == KEY_LEFT)  drawableComponentPlayer->rectangle.x -= calculateDeltaX(physicsComponentPlayer, delta);
            if (inputComponentPlayer->key == KEY_RIGHT) drawableComponentPlayer->rectangle.x += calculateDeltaX(physicsComponentPlayer, delta);
        }
                       
/*
        Ejemplo de gravedad para mapas en 2d en plano normal[generalisimo y plano general] y no en plano cenital[generalisimo y general].
        bool hitObstacle = false;
        for (int i = 0; i < envItemsLength; i++)
        {
            EnvItem* ei = envItems + i;
            Vector2* p = &(player->position);
            if (ei->blocking &&
                ei->rect.x <= p->x &&
                ei->rect.x + ei->rect.width >= p->x &&
                ei->rect.y >= p->y &&
                ei->rect.y <= p->y + player->speed * delta)
            {
                hitObstacle = true;
                player->speed = 0.0f;
                p->y = ei->rect.y;
                break;
            }
        }

        if (!hitObstacle)
        {
            player->position.y += player->speed * delta;
            player->speed += G * delta;
            player->canJump = false;
        }
        else player->canJump = true; */
    }

    void updateEnemy(ScopePtr<Entity>& enemy, float delta) {
        MUST_IMPLEMENT;
    }

    RectangleDrawableComponent* isDrawableComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<RectangleDrawableComponent>();
    }

    InputComponent* isInputComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<InputComponent>();
    }

    PhysicsComponent* isPhysicsComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<PhysicsComponent>();
    }

    CollisionComponent* isCollisionComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<CollisionComponent>();
    }

    PlayerComponent* isPlayerEntity(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<PlayerComponent>();
    }

    float calculateDeltaY(PhysicsComponent* component, float delta) {
        return component->velocity.y * delta + component->speed;
    }

    float calculateDeltaX(PhysicsComponent* component, float delta) {
        return component->velocity.x * delta + component->speed;
    }

private:
    double          m_lastFrame = GetTime();
    EntityContainer m_entities;
};