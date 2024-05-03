#pragma once

#include "../Component/LogicComponents.hpp"
#include "../Component/DrawableComponents.hpp"
#include "./ISystem.hpp"
#include "../Entity/Entity.hpp"

#include <iostream>

class CollisionSystem {
public:
    CollisionSystem(EntityContainer entities) : m_entities(entities) {}
    ~CollisionSystem() {}

   void update() {
        for (ScopePtr<Entity>& entityA : m_entities) {
            CollisionComponent* collisionComponentA = isCollisionComponent(entityA);

            if (!collisionComponentA) {
                continue;
            }

            for (ScopePtr<Entity>& entityB : m_entities) {
                if (*entityA == *entityB) {
                    continue;
                }

                CollisionComponent* collisionComponentB      = isCollisionComponent(entityB);
                RectangleDrawableComponent* rectangleEntityA = isRectangleComponent(entityA);
                RectangleDrawableComponent* rectangleEntityB = isRectangleComponent(entityB);


                if (!collisionComponentB || !rectangleEntityA || !rectangleEntityB) {
                    continue;
                }

                if (CheckCollisionRecs(rectangleEntityA->rectangle, rectangleEntityB->rectangle)) {
                    collisionComponentA->colliding = true;
                    collisionComponentB->colliding = true;
                    
                    rectangleEntityA->color = RED;
                    rectangleEntityB->color = RED;
                    handleCollision(entityA, entityB);
                } else {
                    collisionComponentA->colliding = false;
                    collisionComponentB->colliding = false;
                    
                    rectangleEntityA->color = GOLD;
                    rectangleEntityB->color = GOLD;
                }
            }
        }
    }


private:
    void handleCollision(ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB) {
        return ;
    } 

    CollisionComponent* isCollisionComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<CollisionComponent>();
    }

    RectangleDrawableComponent* isRectangleComponent(ScopePtr<Entity>& entity) {
        return &*entity->getComponent<RectangleDrawableComponent>();
    }

    EntityContainer m_entities;
};