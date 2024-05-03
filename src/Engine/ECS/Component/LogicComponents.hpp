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