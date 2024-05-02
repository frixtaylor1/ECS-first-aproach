#pragma once
#include <raylib.h>
#include "./IComponent.hpp"

/**
 * RectangleDrawableComponent with constructor:
 * 
 * @param float posX
 * @param float posY
 * @param float width
 * @param float height
 * @param Color color
 */
struct RectangleDrawableComponent : implements IDrawableComponent {

    RectangleDrawableComponent(float posX, float posY, float width, float height, Color color);

    virtual ~RectangleDrawableComponent();
    
    Color color{ 
        /* R */ 0,
        /* G */ 0,
        /* B */ 0,
        /* A */ 0 
    };
    Rectangle rectangle{ 
        /* POSX  */ 0.f,
        /* POSY  */ 0.f,
        /* WIDTH */ 0.f,
        /* HEIGHT*/ 0.f 
    };
};

struct ImageDrawableComponent : implements IDrawableComponent {
    ImageDrawableComponent(const Image& image);
    virtual ~ImageDrawableComponent();
    Image image;
};

struct TextureDrawableComponent : implements IDrawableComponent {
    TextureDrawableComponent(const Texture& texture);
    virtual ~TextureDrawableComponent();
    Texture texture;
};
