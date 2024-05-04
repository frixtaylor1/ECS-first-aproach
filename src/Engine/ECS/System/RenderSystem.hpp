#pragma once

#include <vector>

#include "../Entity/Entity.hpp"
#include "../Component/DrawableComponents.hpp"

#include "./ISystem.hpp"

class RenderSystem : implements ISystem
{
public:
    RenderSystem(const EntityContainer entities);
    virtual ~RenderSystem() {}
    void update();

protected:
    RectangleDrawableComponent* isRectangle(ScopePtr<Entity>& entity);

private:
    void renderLogic();
    EntityContainer m_entities;
};