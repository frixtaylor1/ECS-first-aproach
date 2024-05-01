#pragma once

#include <vector>

#include "../Entity/Entity.hpp"
#include "../Component/DrawableComponents.hpp"

class RenderSystem
{
public:
    RenderSystem(std::vector<ScopePtr<Entity> >& entities);
    void render();

protected:
    RectangleDrawableComponent* entityIsRectangle(ScopePtr<Entity>& entity);

private:
    std::vector<ScopePtr<Entity> >& m_entities;
};