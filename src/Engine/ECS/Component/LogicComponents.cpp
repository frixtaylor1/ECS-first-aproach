#include "./LogicComponents.hpp"

MovableComponent::MovableComponent(bool moving) : moving(moving) {}
MovableComponent::~MovableComponent() {}

PhysicsComponent::PhysicsComponent(float speed): speed(speed) {}
PhysicsComponent::~PhysicsComponent() {}

CollisionComponent::CollisionComponent(bool colliding) : colliding(colliding) {}
CollisionComponent::~CollisionComponent() {}