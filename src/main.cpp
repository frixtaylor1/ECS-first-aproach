#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"
#include "./Engine/ECS/System/PhysicsSystem.hpp"
#include "./Engine/ECS/System/InputSystem.hpp"
#include "./Engine/ECS/System/CollisionSystem.hpp"
#include "./Engine/ECS/Component/LogicComponents.hpp"
#include "./Engine/Managers/EntityManager.hpp"

#define FPS_RATE 60

int main(void) {
    const int screenWidth   = 800;
    const int screenHeight  = 600;

    EntityManager entityManager;

    // OPEN WINDOW  //
    // INITIALIZING //
    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
        SetTargetFPS(FPS_RATE);

        // ENTITY ONE...
        entityManager.addEntity(new Entity());
        size_t lastInsertId = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(lastInsertId, 10, GetScreenHeight() / 2.0f - 50, 30, 30, GOLD);
        entityManager.addComponent<PhysicsComponent>(lastInsertId, Vector2{0.f, 0.f}, 30.f, 6.f);
        entityManager.addComponent<MovableComponent>(lastInsertId);
        entityManager.addComponent<InputComponent>(lastInsertId);
        entityManager.addComponent<CollisionComponent>(lastInsertId);
        entityManager.addComponent<PlayerComponent>(lastInsertId);


        // ENTITY TWO...
        entityManager.addEntity(new Entity());
        lastInsertId = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(lastInsertId, 10, GetScreenHeight() / 2.0f - 50, 30 * 2, 30 * 2, BLACK);
        entityManager.addComponent<PhysicsComponent>(lastInsertId, Vector2{0.f, 0.f}, 30.f, 6.f);
        entityManager.addComponent<CollisionComponent>(lastInsertId);


        // ENTITY THREE...
        entityManager.addEntity(new Entity());
        lastInsertId = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<PhysicsComponent>(lastInsertId, Vector2{0.f, 0.f}, 30.f, 6.f);
        entityManager.addComponent<CollisionComponent>(lastInsertId);


        PhysicsSystem           physicsSys(entityManager.getEntities());
        RenderSystem            renderSys(entityManager.getEntities());
        InputSystem             inputSys(entityManager.getEntities());
        CollisionSystem         collisionSys(entityManager.getEntities());

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
        }
        // END MAIN ENGINE LOOP. //
    CloseWindow();
    // CLOSE WINDOW    //
    // DE-INITIALIZING //
    return 0;
}