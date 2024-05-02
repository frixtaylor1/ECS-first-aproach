#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"
#include "./Engine/ECS/System/PhysicsSystem.hpp"
#include "./Engine/ECS/System/InputSystem.hpp"
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

        entityManager.addEntity(new Entity());
        
        size_t lastInsertId = entityManager.getLastInsertEntity()->getId(); 
        entityManager.addComponent<RectangleDrawableComponent>(lastInsertId, 10, GetScreenHeight() / 2.0f - 50, 30, 30, GOLD);
        entityManager.addComponent<PhysicsComponent>(lastInsertId, Vector2{0.f, 0.f}, 30.f, 6.f);
        entityManager.addComponent<MovableComponent>(lastInsertId);
        entityManager.addComponent<InputComponent>(lastInsertId);

        PhysicsSystem<FPS_RATE> physicsSys(entityManager.getEntities());
        RenderSystem renderSys(entityManager.getEntities());
        InputSystem  inputSys(entityManager.getEntities());


        double deltaTime = 0.016;
        double lastFrame = GetTime();

        // START MAIN ENGINE LOOP. //
        while (!WindowShouldClose()) {
            double currentFrame = GetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            inputSys.update();
            physicsSys.update(deltaTime);
            renderSys.render();
        }
        // END MAIN ENGINE LOOP. //
    CloseWindow();
    // CLOSE WINDOW    //
    // DE-INITIALIZING //
    return 0;
}