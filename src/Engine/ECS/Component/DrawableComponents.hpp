#pragma once
#include <raylib.h>
#include "./IComponent.hpp"

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
    virtual ~ImageDrawableComponent();
    Image image;
};

struct TextureDrawableComponent : implements IDrawableComponent {
    virtual ~TextureDrawableComponent();
    Texture texture;
};
