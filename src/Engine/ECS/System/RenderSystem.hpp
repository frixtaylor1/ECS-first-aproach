/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include <vector>

#include "../Entity/Entity.hpp"
#include "./ISystem.hpp"

#include <unordered_map>
#include <functional>

class RenderSystem : implements ISystem
{
private:
    using RenderHandler = std::function<void(ScopePtr<Entity>&)>;
public:
    RenderSystem(EntityContainer entities);
    virtual ~RenderSystem() {}

    void update();
    void setRenderHandler(size_t entityId, RenderHandler handler);
    void setRenderHandler(RenderHandler handler);

private:
    void renderLogic();
    IDrawableComponent* isRenderable(ScopePtr<Entity>& entity);

private:
    EntityContainer m_entities;
    std::vector<RenderHandler, StaticVectorAllocator<RenderHandler, 124>> m_renderHandlerByComponent;
    std::unordered_map<int, RenderHandler>  m_renderHandlers;
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