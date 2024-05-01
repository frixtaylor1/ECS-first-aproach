#include "./DrawableComponents.hpp"

RectangleDrawableComponent::RectangleDrawableComponent(float posX, float posY, float width, float height, Color color)
    : color(color), rectangle({ posX, posY, width, height }) {}

RectangleDrawableComponent::~RectangleDrawableComponent() {
}

ImageDrawableComponent::~ImageDrawableComponent() {}

TextureDrawableComponent::~TextureDrawableComponent() {}
