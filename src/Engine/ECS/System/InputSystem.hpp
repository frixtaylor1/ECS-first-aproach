#pragma once

#include <functional>

#include "../Entity/Entity.hpp"
#include "../Component/LogicComponents.hpp"
#include "./ISystem.hpp"

class InputSystem : implements ISystem {
private:
  using Function = std::function<void()>;
public:
    InputSystem(EntityContainer entities);
    virtual ~InputSystem();

    void update();
    void inputListener(bool isPressed, Function callback);

private:
    InputComponent* isInputComponent(ScopePtr<Entity>& entity);

    EntityContainer m_entities;
};