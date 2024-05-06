#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/System/RenderSystem.hpp"
#include "./Engine/ECS/System/PhysicsSystem.hpp"
#include "./Engine/ECS/System/InputSystem.hpp"
#include "./Engine/ECS/System/CollisionSystem.hpp"
#include "./Engine/ECS/Component/LogicComponents.hpp"
#include "./Engine/Managers/EntityManager.hpp"
#include "./Engine/Managers/SystemManager.hpp"
#include "./Engine/Utils/Allocators/LinealAllocator.hpp"
#include <math.h>
#define FPS_RATE 60


class GameEngine {
public:
    GameEngine() 
        : m_systemManager(new SystemManager()), m_entityManager(new EntityManager()) {
        initialize();
    }

    void run() {
        while(!WindowShouldClose()) {
            for (ScopePtr<ISystem>& system : m_systemManager->getSystems()) {
                system->update();
            }
            m_entityManager->update();
        }

    }

    ScopePtr<SystemManager, true>& getSystemManage() {
        return m_systemManager;
    }

    ScopePtr<EntityManager, true>& getEntityMAnager() {
        return m_entityManager;
    }

private:
    void initialize() {
        m_systemManager->addSystem<InputSystem>(m_entityManager->getEntities());
        m_systemManager->addSystem<PhysicsSystem>(m_entityManager->getEntities());
        m_systemManager->addSystem<CollisionSystem>(m_entityManager->getEntities());
        m_systemManager->addSystem<RenderSystem>(m_entityManager->getEntities());
    }

private:
    ScopePtr<SystemManager, true>   m_systemManager;
    ScopePtr<EntityManager, true>   m_entityManager;
};

int main(void) {
    const int screenWidth   = 800;
    const int screenHeight  = 600;

    GameEngine gameEngine;
    ScopePtr<EntityManager, true>& entityManager = gameEngine.getEntityMAnager();
    ScopePtr<SystemManager, true>& systemManager = gameEngine.getSystemManage();

    LinealAllocator<Entity> allocator;

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
            entityManager->addEntity(new (allocator) Entity()); 
            size_t lasInsertId = entityManager->getLastInsertEntity()->getId();
            entityManager->addComponent<RectangleDrawableComponent>(lasInsertId, posX, posY, 30, 30, Color{
                randomColor.r,
                randomColor.g,
                randomColor.b,
                255
            });
            entityManager->addComponent<PhysicsComponent>(lasInsertId);
        }

        RenderSystem* renderSys = systemManager->getSystem<RenderSystem>();
        renderSys->setRenderHandler([](ScopePtr<Entity>& entity){
            if (auto&& rectangleEntity = entity->getComponent<RectangleDrawableComponent>()) {
                DrawRectangleRec(rectangleEntity->rectangle, rectangleEntity->color);
            }
        });

        PhysicsSystem* physicsSys = systemManager->getSystem<PhysicsSystem>();
        physicsSys->setPhysicsHandler([](ScopePtr<Entity>& entity, float deltaTime) {
            PhysicsComponent* physicsComponent = entity->getComponent<PhysicsComponent>();
            RectangleDrawableComponent* rectangleComponent = entity->getComponent<RectangleDrawableComponent>();

            const int screenHeight = GetScreenHeight();
            const int screenWidth = GetScreenWidth();

            float gravity = 600.0f;
            float bounceFactor = 0.6f;
            float lateralMovement = 10.0f;

            physicsComponent->velocity.y += gravity * deltaTime;

            physicsComponent->velocity.x = lateralMovement * sin(GetTime());

            if (rectangleComponent->rectangle.y + rectangleComponent->rectangle.height >= screenHeight) {
                physicsComponent->velocity.y *= -bounceFactor;

                rectangleComponent->rectangle.y = screenHeight - rectangleComponent->rectangle.height;
            }

            if (rectangleComponent->rectangle.x <= 0 || rectangleComponent->rectangle.x + rectangleComponent->rectangle.width >= screenWidth) {
                physicsComponent->velocity.x *= -bounceFactor;
            }

            rectangleComponent->rectangle.x += physicsComponent->velocity.x * deltaTime;
            rectangleComponent->rectangle.y += physicsComponent->velocity.y * deltaTime;
        });

        // START MAIN ENGINE LOOP. //
        while (!WindowShouldClose()) {
            /* INPUT SYSTEM */
            /* inputSys.update(); */
            /* INPUT SYSTEM */

            /* PHYSISCS SYSTEM */
            /* physicsSys.update(); */
            /* PHYSISCS SYSTEM */

            /* COLLITION SYSTEM */
            /* collisionSys.update(); */
            /* COLLITION SYSTEM */

            /* RENDER SYSTEM */
            /* renderSys.update(); */
            /* RENDER SYSTEM */

            /* entityManager->update(); */

            gameEngine.run();
        }
        // END MAIN ENGINE LOOP. //
    CloseWindow();
    // CLOSE WINDOW    //
    // DE-INITIALIZING //
    return 0;
}