#pragma once

#include "./IComponent.hpp"

struct MovableComponent : implements IComponent {
    virtual ~MovableComponent();
    bool moving;
};

struct PhysicsComponent : implements IComponent {
    virtual ~PhysicsComponent();
    float speed;
};

struct CollisionComponent : implements IComponent {
    virtual ~CollisionComponent();
    bool colliding;
};