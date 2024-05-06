#include "./Engine.hpp"

Engine::Engine(const WindowProps& windowProps, float fpsRate)
    : m_windowProps(windowProps), m_fpsRate(fpsRate),
    m_systemManager(new SystemManager()), m_entityManager(new EntityManager()) {
    initialize();
}

Engine::~Engine() {
    CloseWindow();
}

void Engine::run() {
    while (!WindowShouldClose()) {
        for (ScopePtr<ISystem>& system : m_systemManager->getSystems()) {
            system->update();
        }
        m_entityManager->update();
    }
}

ScopePtr<SystemManager, true>& Engine::getSystemManage() {
    return m_systemManager;
}

ScopePtr<EntityManager, true>& Engine::getEntityMAnager() {
    return m_entityManager;
}

const WindowProps& Engine::getWindowProps() const {
    return m_windowProps;
}

float Engine::getFpsRate() const {
    return m_fpsRate;
}

void Engine::initialize() {
    InitWindow(
        m_windowProps.width,
        m_windowProps.height,
        m_windowProps.title
    );
    SetTargetFPS(FPS_RATE);
    initializeSystems();
}

void Engine::initializeSystems() {
    m_systemManager->addSystem<InputSystem>(m_entityManager->getEntities());
    m_systemManager->addSystem<PhysicsSystem>(m_entityManager->getEntities());
    m_systemManager->addSystem<CollisionSystem>(m_entityManager->getEntities());
    m_systemManager->addSystem<RenderSystem>(m_entityManager->getEntities());
}
