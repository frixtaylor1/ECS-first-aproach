/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#include "./RenderSystem.hpp"
#include "../Component/IComponent.hpp"
#include "../Component/DrawableComponents.hpp"

RenderSystem::RenderSystem() = default;
RenderSystem::~RenderSystem() = default;

void RenderSystem::update(ScopePtr<Entity>& entity) {
    renderLogic(entity);
}

void RenderSystem::renderLogic(ScopePtr<Entity>& entity) {
    if (!isRenderable(entity)) {
        return;
    }
    for (RenderHandler& renderHandler : m_renderHandlerByComponent) {
        renderHandler(entity);
    }
    RenderHandler handler = m_renderHandlers[entity->getId()];
    if (handler) {
        handler(entity);
    }
}

void RenderSystem::setRenderHandler(size_t entityId, RenderHandler handler) {
    m_renderHandlers[entityId] = handler;
}

void RenderSystem::setRenderHandler(RenderHandler handler) {
    m_renderHandlerByComponent.push_back(std::move(handler));
}

IDrawableComponent* RenderSystem::isRenderable(ScopePtr<Entity>& entity){
    return entity->getComponent<IDrawableComponent>();
}

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