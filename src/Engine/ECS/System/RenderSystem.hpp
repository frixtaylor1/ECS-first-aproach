#pragma once

#include <vector>

#include "../Entity/Entity.hpp"
#include "../Component/DrawableComponents.hpp"

class RenderSystem
{
public:
    RenderSystem(std::vector<ScopePtr<Entity>, StaticAllocator<Entity, 1024> >& entities);
    void render();

protected:
    RectangleDrawableComponent* entityIsRectangle(ScopePtr<Entity>& entity);

private:
    void renderLogic();

    std::vector<ScopePtr<Entity>, StaticAllocator<Entity, 1024> >& m_entities;
};