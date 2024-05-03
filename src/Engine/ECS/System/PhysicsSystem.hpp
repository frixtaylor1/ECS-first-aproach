#pragma once

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"
#include "./InputSystem.hpp"

template <int FramePerSeconds = 60>
class PhysicsSystem : implements ISystem {
public:
    PhysicsSystem(const EntityContainer entities) : m_entities(entities) {}

    void update(float delta, InputSystem& inputSystem) {
        for (ScopePtr<Entity>& entity : m_entities) {

            PhysicsComponent*           physicsComponent    = isPhysicsComponent(entity);
            InputComponent*             inputComponent      = isInputComponent(entity);
            RectangleDrawableComponent* drawableComponent   = isDrawableComponent(entity);

            if (!physicsComponent || !inputComponent || !drawableComponent) {
                continue;
            }

            if (inputComponent->keyPressed) {
                inputSystem.inputListener(inputComponent->key == KEY_UP, [&]() {
                    drawableComponent->rectangle.y -= calculateDeltaY(physicsComponent, delta);
                });
                inputSystem.inputListener(inputComponent->key == KEY_DOWN, [&]() {
                    drawableComponent->rectangle.y += calculateDeltaY(physicsComponent, delta);
                });
                inputSystem.inputListener(inputComponent->key == KEY_LEFT, [&]() {
                    drawableComponent->rectangle.x -= calculateDeltaX(physicsComponent, delta);
                });
                inputSystem.inputListener(inputComponent->key == KEY_RIGHT, [&]() {
                    drawableComponent->rectangle.x += calculateDeltaX(physicsComponent, delta);
                });
            }
        }
    }
private:
    RectangleDrawableComponent* isDrawableComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<RectangleDrawableComponent>();
    }

    InputComponent* isInputComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<InputComponent>();
    }

    PhysicsComponent* isPhysicsComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<PhysicsComponent>();
    }

    float calculateDeltaY(PhysicsComponent* component, float delta) {
        return component->velocity.y * delta + component->speed;
    }

    float calculateDeltaX(PhysicsComponent* component, float delta) {
        return component->velocity.x * delta + component->speed;
    }

    EntityContainer m_entities;
};