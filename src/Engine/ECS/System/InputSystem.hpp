#pragma once

#include <functional>

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "./ISystem.hpp"

class InputSystem : implements ISystem {
private:
  using Function = std::function<void()>;
public:
    InputSystem(EntityContainer entities) : m_entities(entities) {}
    ~InputSystem() {}

    void update() {
        for (ScopePtr<Entity>& entity : m_entities) {
            InputComponent* inputComponent = isInputComponent(entity);
            if (inputComponent) {
                inputComponent->key = GetKeyPressed();
                if (IsKeyPressed(inputComponent->key)) {
                    inputComponent->keyPressed = true;
                } else {
                    inputComponent->keyPressed = false;
                }
            }
        }
    }

    void inputListener(bool isPressed, Function callback) {
        if (isPressed) {
            callback();
        }
    }

private:
    InputComponent* isInputComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<InputComponent>();
    }

    EntityContainer m_entities;
};