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
    const int screenWidth   = 800;
    const int screenHeight  = 600;

    LinealAllocator<Entity> allocator;

    EntityManager entityManager;

    // OPEN WINDOW  //
    // INITIALIZING //
    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
        SetTargetFPS(FPS_RATE);
        std::cout << "WEIGHT OF A ENTITY: " << sizeof(ScopePtr<Entity>) << std::endl; 

        for (size_t idxEntity = 0; idxEntity < 10000; idxEntity++) {
            // Generate random position and size for the entity
            int posX = rand() % screenWidth;
            int posY = rand() % screenHeight;
            Color randomColor;
            randomColor.r = rand() % 256;
            randomColor.g = rand() % 256;
            randomColor.b = rand() % 256;
            randomColor.a = 255;
            entityManager.addEntity(new (allocator) Entity()); 
            size_t lasInsertId = entityManager.getLastInsertEntity()->getId();
            entityManager.addComponent<RectangleDrawableComponent>(lasInsertId, posX, posY, 30, 30, Color{
                randomColor.r,
                randomColor.g,
                randomColor.b,
                randomColor.a
            });
        }

        // SYSTEMS...
        PhysicsSystem   physicsSys(entityManager.getEntities());
        RenderSystem    renderSys(entityManager.getEntities());
        InputSystem     inputSys(entityManager.getEntities());
        CollisionSystem collisionSys(entityManager.getEntities());

        renderSys.setRenderHandler([](ScopePtr<Entity>& entity){
            if (auto&& rectangleEntity = entity->getComponent<RectangleDrawableComponent>()) {
                DrawRectangleRec(rectangleEntity->rectangle, rectangleEntity->color);
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

            entityManager.update();
        }
        // END MAIN ENGINE LOOP. //
    CloseWindow();
    // CLOSE WINDOW    //
    // DE-INITIALIZING //
    return 0;
}