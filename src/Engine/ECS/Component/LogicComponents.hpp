/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include "./IComponent.hpp"

/**
 * MovableComponent structure.
 * Constructor with parameters...
 *
 * @param bool moving
 */
struct MovableComponent : implements IComponent {
    MovableComponent() = default;
    MovableComponent(bool moving);
    virtual ~MovableComponent();
    bool moving;
};

/**
 * PysicsCompoent structure.
 * Constructor with parameters...
 *
 * @param Vector2       - velocity
 * @param float         - speed
 * @param velocityLimit - velocityLimit
 */
struct PhysicsComponent : implements IComponent {
    PhysicsComponent() = default;
    /**
     * @param Vector2 velocity
     */
    PhysicsComponent(Vector2 velocity, float speed, float velocityLimit);
    virtual ~PhysicsComponent();

    Vector2 velocity;
    float speed;
    float velocityLimit;
};

/**
 * CollisionComponent structure.
 * Constructor with parameters...
 *
 * @param bool colliding
 */
struct CollisionComponent : implements IComponent {
    CollisionComponent() = default;
    CollisionComponent(bool colliding);
    virtual ~CollisionComponent();
    bool colliding;
};

/**
 * SolidComponent structure.
 * Constructor with parameters...
 *
 * @param bool solid
 */
struct SolidComponent : implements IComponent {
    SolidComponent() = default;
    SolidComponent(bool solid);
    virtual ~SolidComponent();
    bool solid;
};

/**
 * ControllableComponent structure.
 */
struct InputComponent : implements IComponent {
    typedef int Key;
    bool keyPressed;
    Key  key;
};

/**
 * PlayerComponent structure.
 * Constructor with parameters...
 *
 * @param int score
 * @param int* bombs
 */
struct PlayerComponent : implements IComponent {
    virtual ~PlayerComponent();
    enum { BOMS_CAP = 1 };
    int score = 0;
    int bombs[BOMS_CAP] = {0};
};

struct EnemyComponent : implements IComponent {
    virtual ~EnemyComponent();
};

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