#include "./RenderSystem.hpp"

RenderSystem::RenderSystem(std::vector<ScopePtr<Entity>, StaticAllocator<Entity, 1024>>& entities)
    : m_entities(entities) {}

void RenderSystem::render() {
    /*BEGIN DRAWING*/
    BeginDrawing();
        renderLogic();
    EndDrawing();
    /*END DRAWING*/
}

void RenderSystem::renderLogic() {
    ClearBackground(LIGHTGRAY);

    for (ScopePtr<Entity>& entity : m_entities) {
        if (RectangleDrawableComponent* rectangleEntity = isRectangle(entity)) {
            DrawRectangleRec(rectangleEntity->rectangle, rectangleEntity->color);
        }
    }
}

RectangleDrawableComponent* RenderSystem::isRectangle(ScopePtr<Entity>& entity) {
    if (auto rectangle = entity.get()->getComponent<RectangleDrawableComponent>()) {
        return rectangle;
    }
    return nullptr;
}