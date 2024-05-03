#pragma once

#include "../ECS/System/PhysicsSystem.hpp"
#include "../ECS/System/RenderSystem.hpp"
#include "../ECS/System/InputSystem.hpp"

#define FPS_RATE 60

class SystemManager {
public:
    SystemManager(PhysicsSystem<FPS_RATE>& physicsSystem, RenderSystem& renderSystem, InputSystem& inputSystem)
        : m_physicsSystem(physicsSystem), m_renderSystem(renderSystem), m_inputSystem(inputSystem) {}

    ~SystemManager() {}

private:

    const RenderSystem& getRenderSystem() const {
        return m_renderSystem;
    }

    const InputSystem& getInputSystem() const {
        return m_inputSystem;
    }

    const PhysicsSystem<FPS_RATE>& getPhysicsSystem() const {
        return m_physicsSystem;
    }

    PhysicsSystem<FPS_RATE>& m_physicsSystem;
    RenderSystem& m_renderSystem;
    InputSystem& m_inputSystem;
};