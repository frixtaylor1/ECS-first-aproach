#pragma once

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "./ISystem.hpp"

class InputSystem : implements ISystem {
public:
    InputSystem(EntityContainer entities) : m_entities(entities) {}
    ~InputSystem() {}

    void update() {
        for (ScopePtr<Entity>& entity : m_entities) {
            if (InputComponent* inputComponent = isInputComponent(entity)) {
                inputComponent->key = GetKeyPressed();
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

    EntityContainer m_entities;
};