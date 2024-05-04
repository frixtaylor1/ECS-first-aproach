#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"
#include "./Engine/ECS/System/PhysicsSystem.hpp"
#include "./Engine/ECS/System/InputSystem.hpp"
#include "./Engine/ECS/System/CollisionSystem.hpp"
#include "./Engine/ECS/Component/LogicComponents.hpp"
#include "./Engine/Managers/EntityManager.hpp"
#include "./Engine/Utils/Allocators/LinealAllocator.hpp"

#define FPS_RATE 60


int main(void) {
    typedef LinealAllocator<Entity> MyEntityAllocator;
    MyEntityAllocator entityAllocator;

    const int screenWidth   = 800;
    const int screenHeight  = 600;

    EntityManager entityManager;

    // OPEN WINDOW  //
    // INITIALIZING //
    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
        SetTargetFPS(FPS_RATE);

        // ENTITY ONE...
        entityManager.addEntity(new (entityAllocator) Entity()); 
        size_t idEntityA = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(idEntityA, 10, GetScreenHeight() / 2.0f - 50, 30, 30, GOLD);
        entityManager.addComponent<PhysicsComponent>(idEntityA, Vector2{0.f, 0.f}, 30.f, 6.f);
        entityManager.addComponent<MovableComponent>(idEntityA);
        entityManager.addComponent<InputComponent>(idEntityA);
        entityManager.addComponent<CollisionComponent>(idEntityA);
        entityManager.addComponent<PlayerComponent>(idEntityA);


        // ENTITY TWO...
        entityManager.addEntity(new (entityAllocator) Entity());
        size_t idEntityB = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(idEntityB, GetScreenWidth() - (30 * 2) - 10, GetScreenHeight() / 2.0f - 50, 30 * 2, 30 * 2, BLACK);
        entityManager.addComponent<PhysicsComponent>(idEntityB, Vector2{0.f, 0.f}, 30.f, 6.f);
        entityManager.addComponent<CollisionComponent>(idEntityB);
        entityManager.addComponent<EnemyComponent>(idEntityB);


        // ENTITY THREE...
        entityManager.addEntity(new (entityAllocator) Entity());
        size_t idEntityC = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<PhysicsComponent>(idEntityC, Vector2{0.f, 0.f}, 30.f, 6.f);


        // SYSTEMS...
        PhysicsSystem   physicsSys(entityManager.getEntities());
        RenderSystem    renderSys(entityManager.getEntities());
        InputSystem     inputSys(entityManager.getEntities());
        CollisionSystem collisionSys(entityManager.getEntities());


        // TEST COLLISION CALLBACK... //
        collisionSys.setCollisionHandler(idEntityA, idEntityB, [&](ScopePtr<Entity>& entityA, ScopePtr<Entity>& entityB) {
            PlayerComponent* playerComponentEntityA = entityA->getComponent<PlayerComponent>();
            EnemyComponent*  enemyComponentEntityB  = entityB->getComponent<EnemyComponent>();
            if (!playerComponentEntityA && !enemyComponentEntityB) {
                return;
            }

            RectangleDrawableComponent* drawableComponentA = entityA->getComponent<RectangleDrawableComponent>();
            drawableComponentA->color = RED;

            RectangleDrawableComponent* drawableComponentB = entityB->getComponent<RectangleDrawableComponent>();
            drawableComponentB->color = GREEN;

            CollisionComponent* collA = entityA->getComponent<CollisionComponent>();
            CollisionComponent* collB = entityB->getComponent<CollisionComponent>();
            if (collA->colliding && collB->colliding) {
                entityManager.removeEntity(idEntityA);
            }

            if (!collA->colliding && !collB->colliding) {
                drawableComponentA->color = GREEN;
                drawableComponentB->color = GOLD;
            }
        });

        physicsSys.setPhysicsHandler(idEntityA, [](ScopePtr<Entity>& entityA, float delta) {
            if (!entityA->getComponent<PlayerComponent>()) {
                return;
            }
            InputComponent* inputComponentPlayer                = entityA->getComponent<InputComponent>();
            PhysicsComponent* physicsComponentPlayer            = entityA->getComponent<PhysicsComponent>();
            RectangleDrawableComponent* drawableComponentPlayer = entityA->getComponent<RectangleDrawableComponent>();

            std::function<float(PhysicsComponent* component, float delta)>
                calculateDeltaY = [](PhysicsComponent* component, float delta) {
                return component->velocity.y * delta + component->speed;
            };

            std::function<float(PhysicsComponent* component, float delta)>
                calculateDeltaX = [](PhysicsComponent* component, float delta) {
                return component->velocity.x * delta + component->speed;
            };

            if (inputComponentPlayer->keyPressed) {
                if (inputComponentPlayer->key == KEY_UP)    drawableComponentPlayer->rectangle.y -= calculateDeltaY(physicsComponentPlayer, delta);
                if (inputComponentPlayer->key == KEY_DOWN)  drawableComponentPlayer->rectangle.y += calculateDeltaY(physicsComponentPlayer, delta);
                if (inputComponentPlayer->key == KEY_LEFT)  drawableComponentPlayer->rectangle.x -= calculateDeltaX(physicsComponentPlayer, delta);
                if (inputComponentPlayer->key == KEY_RIGHT) drawableComponentPlayer->rectangle.x += calculateDeltaX(physicsComponentPlayer, delta);
            }
        });

        // START MAIN ENGINE LOOP. //
        while (!WindowShouldClose()) {
            /* INPUT SYSTEM */
            inputSys.update();
            /* INPUT SYSTEM */

            /* PHYSISCS SYSTEM */
            physicsSys.update();
            /* PHYSISCS SYSTEM */

            /* COLLITION SYSTEM */
            collisionSys.update();
            /* COLLITION SYSTEM */

            /* RENDER SYSTEM */
            renderSys.update();
            /* RENDER SYSTEM */

            entityManager.removeMarkedEntities();
        }
        // END MAIN ENGINE LOOP. //
    CloseWindow();
    // CLOSE WINDOW    //
    // DE-INITIALIZING //
    return 0;
}