#include <iostream>
#include "./Engine/Engine.hpp"
#include "./Engine/Utils/Allocators/LinealAllocator.hpp"

void initializeEntities(EntityManager* entityManager, WindowProps const& windowProps);
void initializeRenderHandler(RenderSystem* renderSys, Camera3D& camera);
void initializePhysicsHandlers(PhysicsSystem* physicsSys);

int main() {
    Engine*         gameEngine      = new Engine({ 800, 600, "Cubo Giratorio en 3D" });
    EntityManager*  entityManager   = gameEngine->getEntityManager().get();
    SystemManager*  systemManager   = gameEngine->getSystemManager().get();

    initializeEntities(entityManager, gameEngine->getWindowProps());
    
    Camera3D camera     = { 0 };
    camera.position     = { 50.0f, 50.0f, 50.0f };
    camera.target       = { 0.0f, 25.0f, 0.0f };
    camera.up           = { 0.0f, 1.0f, 0.0f };
    camera.fovy         = 45.0f;
    camera.projection   = CAMERA_PERSPECTIVE;

    PhysicsSystem*  physicsSystem = systemManager->getSystem<PhysicsSystem>(); 
    RenderSystem*   renderSystem  = systemManager->getSystem<RenderSystem>();

    initializePhysicsHandlers(physicsSystem);
    initializeRenderHandler(renderSystem, camera);

    gameEngine->run();

    delete gameEngine;
    return 0;
}

void initializeEntities(EntityManager* entityManager, WindowProps const& windowProps) {
    LOG_MESSAGE("Inicializando entidades...");
    for (size_t idx = 0; idx < 1000; idx++) {
        float xPos = GetRandomValue(-windowProps.width / 2, windowProps.width / 2);
        float yPos = GetRandomValue(20, 50);
        float zPos = GetRandomValue(-windowProps.height / 2, windowProps.height / 2);

        entityManager->addEntity(new Entity());
        entityManager->addComponent<CubeDrawableComponent>(
            idx,
            Vector3{ xPos, yPos, zPos },
            2.0f,
            RED
        );
        entityManager->addComponent<PhysicsComponent>(idx);
    }
}

void initializeRenderHandler(RenderSystem* renderSys, Camera3D& camera) {
    renderSys->setRenderHandler([&camera](ScopePtr<Entity>& entity) {
        CubeDrawableComponent* cubeEntity = entity->getComponent<CubeDrawableComponent>();
        
        BeginMode3D(camera);
            DrawCube(
                cubeEntity->cubePos,
                cubeEntity->size,
                cubeEntity->size,
                cubeEntity->size,
                cubeEntity->color
            );
        EndMode3D();

        DrawFPS(10, 10);
    });
}

void initializePhysicsHandlers(PhysicsSystem* physicsSys) {
    physicsSys->setPhysicsHandler([](ScopePtr<Entity>& entity, float deltaTime) {
        PhysicsComponent*       physicsComponent    = entity->getComponent<PhysicsComponent>();
        CubeDrawableComponent*  cubeComponent       = entity->getComponent<CubeDrawableComponent>();

        // Simulación de la gravedad
        float gravity = 9.81f;
        physicsComponent->velocity.y -= gravity * deltaTime;

        // Movimiento horizontal aleatorio
        if (cubeComponent->cubePos.y <= 0) {
            physicsComponent->velocity.x = 0;
        }

        cubeComponent->cubePos.x += physicsComponent->velocity.x * deltaTime;
        cubeComponent->cubePos.y += physicsComponent->velocity.y * deltaTime;
        cubeComponent->cubePos.z += physicsComponent->velocity.z * deltaTime;

        if (cubeComponent->cubePos.y <= 0) {
            physicsComponent->velocity.y *= -0.6f;
            physicsComponent->bounceCount++;

            if (physicsComponent->bounceCount >= 2) {
                physicsComponent->velocity.y    = 0;
                physicsComponent->bounceCount   = 0;
            }
        }
    });
}
