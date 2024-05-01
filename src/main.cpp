#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"
#include "./Engine/Managers/EntityManager.hpp"

int main(void) {
    const int screenWidth   = 800;
    const int screenHeight  = 600;

    EntityManager entityManager;

    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
        SetTargetFPS(60);

        entityManager.addEntity(new Entity());
        const size_t lastInsertId = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(lastInsertId, 
            10, GetScreenHeight() / 2.0f - 50, 200, 100, GOLD
        );

        RenderSystem renderSys(entityManager.getEntities());
        // MAIN ENGINE LOOP...
        while (!WindowShouldClose()) {
            renderSys.render();
        }
    CloseWindow();

    return 0;
}