/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

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
    auto& entities = m_entityManager->getEntities();
    size_t idx = 0;
    while (m_isRunning) {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            m_systemManager->getSystem<InputSystem>()->update(entities[idx]);
            m_systemManager->getSystem<CollisionSystem>()->update(entities[idx]);
            m_entityManager->update();
        
            for (ScopePtr<Entity>& entity : entities) {
                m_systemManager->getSystem<PhysicsSystem>()->update(entity);
                m_systemManager->getSystem<RenderSystem>()->update(entity);
            }
            
            m_isRunning = !WindowShouldClose();
        EndDrawing();
        
        if (idx == entities.size()) idx = 0;
    }
}

ScopePtr<SystemManager>& Engine::getSystemManager() {
    return m_systemManager;
}

ScopePtr<EntityManager>& Engine::getEntityManager() {
    return m_entityManager;
}

const WindowProps& Engine::getWindowProps() const {
    return m_windowProps;
}

float Engine::getFpsRate() const {
    return m_fpsRate;
}

void Engine::initialize() {
    m_isRunning = true;
    InitWindow(
        m_windowProps.width,
        m_windowProps.height,
        m_windowProps.title
    );
    SetTargetFPS(FPS_RATE);
    initializeSystems();
}

void Engine::initializeSystems() {
    m_systemManager->addSystem<InputSystem>();
    m_systemManager->addSystem<PhysicsSystem>();
    m_systemManager->addSystem<CollisionSystem>(m_entityManager->getEntities());
    m_systemManager->addSystem<RenderSystem>();
}

/**  
 * MIT License
 *  
 * Copyright (c) 2024 Kevin Daniel Taylor
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */