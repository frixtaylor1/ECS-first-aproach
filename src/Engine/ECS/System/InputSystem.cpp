#include "./InputSystem.hpp"

InputSystem::InputSystem(EntityContainer entities) : m_entities(entities) {}
InputSystem::~InputSystem() {}

void InputSystem::update() {
    for (ScopePtr<Entity>& entity : m_entities) {
        InputComponent* inputComponent = isInputComponent(entity);
        if (inputComponent) {
            inputComponent->key = GetKeyPressed();
            if (IsKeyPressed(inputComponent->key)) {
                inputComponent->keyPressed = true;
            }
            else {
                inputComponent->keyPressed = false;
            }
        }
    }
}

void InputSystem::inputListener(bool isPressed, Function callback) {
    if (isPressed) { callback(); }
}

InputComponent* InputSystem::isInputComponent(ScopePtr<Entity>& entity) {
    return entity->getComponent<InputComponent>();
}
