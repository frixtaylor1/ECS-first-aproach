#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
        SetTargetFPS(60);

        ScopePtr<Entity> player1(new Entity());
        player1->addComponent<RectangleDrawableComponent>(
            10, GetScreenHeight() / 2.0f - 50, 200, 100, GOLD);

        std::vector<ScopePtr<Entity>> entities;
        entities.emplace_back(std::move(player1));

        RenderSystem renderSys(entities);
        // MAIN ENGINE LOOP...
        while (!WindowShouldClose()) {
            renderSys.render();
        }
    CloseWindow();

    return 0;
}