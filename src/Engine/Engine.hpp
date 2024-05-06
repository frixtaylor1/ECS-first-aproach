#pragma once

#include "./Managers/EntityManager.hpp"
#include "./Managers/SystemManager.hpp"

#define FPS_RATE 60

struct WindowProps {
    int width;
    int height;
    const char* title;
};

class Engine {
private:
public:
    Engine(const WindowProps& windowProps, float fpsRate = FPS_RATE);
    ~Engine();

    void run();
    ScopePtr<SystemManager, true>& getSystemManage();
    ScopePtr<EntityManager, true>& getEntityMAnager();
    const WindowProps& getWindowProps() const;
    float getFpsRate() const;

private:
    void initialize();
    void initializeSystems();

private:
    WindowProps                     m_windowProps;
    float                           m_fpsRate;
    ScopePtr<SystemManager, true>   m_systemManager;
    ScopePtr<EntityManager, true>   m_entityManager;
};

#include "./ECS/System/RenderSystem.hpp"
#include "./ECS/System/PhysicsSystem.hpp"
#include "./ECS/System/InputSystem.hpp"
#include "./ECS/System/CollisionSystem.hpp"