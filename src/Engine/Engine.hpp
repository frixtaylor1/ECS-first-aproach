/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include "./Managers/EntityManager.hpp"
#include "./Managers/SystemManager.hpp"

#define FPS_RATE 120

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
    ScopePtr<SystemManager>& getSystemManager();
    ScopePtr<EntityManager>& getEntityManager();
    const WindowProps& getWindowProps() const;
    float getFpsRate() const;

private:
    void initialize();
    void initializeSystems();

private:
    WindowProps                     m_windowProps;
    float                           m_fpsRate;
    ScopePtr<SystemManager>         m_systemManager;
    ScopePtr<EntityManager>         m_entityManager;
    bool                            m_isRunning = false;
};

#include "./ECS/System/RenderSystem.hpp"
#include "./ECS/System/PhysicsSystem.hpp"
#include "./ECS/System/InputSystem.hpp"
#include "./ECS/System/CollisionSystem.hpp"

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