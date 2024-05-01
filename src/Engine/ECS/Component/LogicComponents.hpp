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
 * @param float speed
 */
struct PhysicsComponent : implements IComponent {
    PhysicsComponent() = default;
    /**
     * @param float speed
     */
    PhysicsComponent(float speed);
    virtual ~PhysicsComponent();

    float speed;
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