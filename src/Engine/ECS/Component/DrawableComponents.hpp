/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

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

/**  
 * MIT License
 *  
 * Copyright (c) 2024 Kevin Daniel Taylor
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */