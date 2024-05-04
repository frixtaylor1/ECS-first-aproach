#pragma once

#include "../ECS/System/PhysicsSystem.hpp"
#include "../ECS/System/RenderSystem.hpp"
#include "../ECS/System/InputSystem.hpp"

#define FPS_RATE 60

class SystemManager {
public:
    SystemManager() = default;

    SystemManager(const PhysicsSystem& physicsSystem, const RenderSystem& renderSystem, const InputSystem& inputSystem)
        : m_physicsSystem(physicsSystem), m_renderSystem(renderSystem), m_inputSystem(inputSystem) {}

    ~SystemManager() {}

    const RenderSystem&     getRenderSystem()   const { return m_renderSystem;  }
    const InputSystem&      getInputSystem()    const { return m_inputSystem;   }
    const PhysicsSystem&    getPhysicsSystem()  const { return m_physicsSystem; }
    
private:
    PhysicsSystem  m_physicsSystem;
    RenderSystem   m_renderSystem;
    InputSystem    m_inputSystem;
};