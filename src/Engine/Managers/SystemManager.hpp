/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include "../Utils/Allocators/StaticVectorAllocator.hpp"
#include "../ECS/System/ISystem.hpp"

#include <vector>

#define MAX_CAP_SYS 10

class SystemManager {
private:
    using SystemContainer = std::vector<ScopePtr<ISystem>, StaticVectorAllocator<ScopePtr<ISystem>, MAX_CAP_SYS> >;
public:
    SystemManager();
    ~SystemManager();

    template <typename SystemType, typename... Args>
    void addSystem(Args &&...args);

    template <typename SystemType>
    SystemType* getSystem() const noexcept;

    SystemContainer& getSystems();

private:
    SystemContainer m_systems;
};

#include "./SystemManagerImp.hpp"

using SystemContainer =  std::vector<ScopePtr<ISystem>, StaticVectorAllocator<ScopePtr<ISystem>, MAX_CAP_SYS> >&;

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