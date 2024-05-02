#include "./LogicComponents.hpp"

MovableComponent::MovableComponent(bool moving) : moving(moving) {}
MovableComponent::~MovableComponent() {}

PhysicsComponent::PhysicsComponent(Vector2 velocity, float speed, float velocityLimit = 6.f): velocity(velocity), speed(speed), velocityLimit(velocityLimit) {}
PhysicsComponent::~PhysicsComponent() {}

CollisionComponent::CollisionComponent(bool colliding) : colliding(colliding) {}
CollisionComponent::~CollisionComponent() {}