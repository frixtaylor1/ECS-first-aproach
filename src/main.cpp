#include "./Engine/ECS/Entity/Entity.hpp"
#include "./Engine/ECS/Component/LogicComponents.hpp"
#include "./Engine/Managers/EntityManager.hpp"

#include "./Engine/Utils/Allocators/LinealAllocator.hpp"
#include "./Engine/Engine.hpp"
#include <math.h>

void initilizeEntities(EntityManager* entityManager, LinealAllocator<Entity>& allocator, WindowProps const& windowProps);
void setPhysicsHandler(PhysicsSystem* physicsSys, WindowProps const& windowProps);
void setRenderHandler(RenderSystem* renderSys);
void engineDemo();

int main(void) {
    engineDemo();    
    return 0;
}

// IMPL...

void engineDemo() {
    Engine gameEngine({ 800,600, "FRIX GAME ENGINE" });
    ScopePtr<EntityManager, true>& entityManager = gameEngine.getEntityMAnager();
    ScopePtr<SystemManager, true>& systemManager = gameEngine.getSystemManage();

    LinealAllocator<Entity> allocator;

    std::cout << "WEIGHT OF A ENTITY: " << sizeof(ScopePtr<Entity>) << std::endl;

    RenderSystem*   renderSys   = systemManager->getSystem<RenderSystem>();
    PhysicsSystem*  physicsSys  = systemManager->getSystem<PhysicsSystem>();

    initilizeEntities(entityManager.get(), allocator, gameEngine.getWindowProps());
    setPhysicsHandler(physicsSys, gameEngine.getWindowProps());
    setRenderHandler(renderSys);
    
    gameEngine.run();
}

void initilizeEntities(EntityManager* entityManager, LinealAllocator<Entity>& allocator, WindowProps const& windowProps) {    for (size_t idxEntity = 0; idxEntity < 10000; idxEntity++) {
        // Generate random position and size for the entity
        int posX = rand() % windowProps.width;
        int posY = rand() % windowProps.height;
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
}

void setPhysicsHandler(PhysicsSystem* physicsSys, WindowProps const& windowProps) {
    physicsSys->setPhysicsHandler([&windowProps](ScopePtr<Entity>& entity, float deltaTime) {
        PhysicsComponent*           physicsComponent    = entity->getComponent<PhysicsComponent>();
        RectangleDrawableComponent* rectangleComponent  = entity->getComponent<RectangleDrawableComponent>();

        const int screenHeight  = windowProps.height;
        const int screenWidth   = windowProps.width;

        float gravity           = 600.0f;
        float bounceFactor      = 0.6f;
        float lateralMovement   = 10.0f;

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
}

void setRenderHandler(RenderSystem* renderSys) {
    renderSys->setRenderHandler([](ScopePtr<Entity>& entity) {
        if (auto&& rectangleEntity = entity->getComponent<RectangleDrawableComponent>()) {
            DrawRectangleRec(rectangleEntity->rectangle, rectangleEntity->color);
        }
    });
}