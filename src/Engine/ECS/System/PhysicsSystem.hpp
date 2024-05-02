#pragma once

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"

template <int FramePerSeconds = 60>
class PhysicsSystem : implements ISystem {
public:
    PhysicsSystem(const EntityContainer entities) : m_entities(entities) {}

    void update(float delta = 0.16f) {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (InputComponent* inputComponent = isInputComponent(entity)) {
                if (IsKeyPressed(inputComponent->key)) {
                    if (PhysicsComponent* physicsComponent = isPhysicsComponent(entity)) {
                        RectangleDrawableComponent* drawableComponent = entity.get()->getComponent<RectangleDrawableComponent>();
                        
                        switch (inputComponent->key) {
                            case KEY_UP:
                            {
                                float deltaY = calculateDeltaY(physicsComponent, delta);
                                drawableComponent->rectangle.y -= deltaY;
                                break;
                            }
                            case KEY_DOWN:
                            {
                                float deltaY = calculateDeltaY(physicsComponent, delta);
                                drawableComponent->rectangle.y += deltaY;
                                break;
                            }
                            case KEY_LEFT:
                            {
                                float deltaX = calculateDeltaX(physicsComponent, delta);
                                drawableComponent->rectangle.x -= deltaX;
                                break;   
                            }
                            case KEY_RIGHT:
                            {
                                float deltaX = calculateDeltaX(physicsComponent, delta);
                                drawableComponent->rectangle.x += deltaX;
                                break;   
                            }
                        }
                    }
                }
            }
        }
    }
private:
    InputComponent* isInputComponent(ScopePtr<Entity>& entity) {
        if (auto component = entity.get()->getComponent<InputComponent>()) {
            return component;
        }
        return nullptr;
    }

    PhysicsComponent* isPhysicsComponent(ScopePtr<Entity>& entity) {
        if (auto component = entity.get()->getComponent<PhysicsComponent>()) {
            return component;
        }
        return nullptr;
    }

    float calculateDeltaY(PhysicsComponent* component, float delta) {
        return component->velocity.y * delta + component->speed;
    }

    float calculateDeltaX(PhysicsComponent* component, float delta) {
        return component->velocity.x * delta + component->speed;
    }

    EntityContainer m_entities;
};