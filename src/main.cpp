#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"
#include "./Engine/ECS/Component/LogicComponents.hpp"
#include "./Engine/Managers/EntityManager.hpp"

int main(void) {
    const int screenWidth   = 800;
    const int screenHeight  = 600;

    EntityManager entityManager;

    // OPEN WINDOW  //
    // INITIALIZING //
    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
        SetTargetFPS(60);

        entityManager.addEntity(new Entity());
        const size_t lastInsertId = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(lastInsertId, 10, GetScreenHeight() / 2.0f - 50, 200, 100, GOLD);
        entityManager.addComponent<PhysicsComponent>(lastInsertId, 3.0f);
        entityManager.addComponent<MovableComponent>(lastInsertId);

        RenderSystem renderSys(entityManager.getEntities());
        
        // MAIN ENGINE LOOP...
        while (!WindowShouldClose()) {
            renderSys.render();
        }
    CloseWindow();
    // CLOSE WINDOW    //
    // DE-INITIALIZING //
    return 0;
}