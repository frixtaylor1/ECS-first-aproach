#include "./RenderSystem.hpp"

#include <raylib.h>

RenderSystem::RenderSystem(std::vector<ScopePtr<Entity>>& entities)
    : m_entities(entities) {}

void RenderSystem::render() {
    /*BEGIN DRAWING*/
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (auto&& entity : m_entities) {
        if (auto rectangleEntity = entityIsRectangle(entity)) {
            DrawRectangleRec(rectangleEntity->rectangle, rectangleEntity->color);
        }
    }
    EndDrawing();
    /*END DRAWING*/
}

RectangleDrawableComponent* RenderSystem::entityIsRectangle(ScopePtr<Entity>& entity) {
    if (auto rectangle = entity.get()->getComponent<RectangleDrawableComponent>()) {
        return rectangle;
    }
    return nullptr;
}