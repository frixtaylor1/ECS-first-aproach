/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include <typeinfo>
#include <cstddef>
#include <array>

template<class ItemType, size_t CAP_ARENA = 1024>
class LinealAllocator {
public:
    using value_type = ItemType;

    LinealAllocator() noexcept;
    ~LinealAllocator() noexcept;

    template<typename U>
    LinealAllocator(const LinealAllocator<U>&) noexcept;

    template<typename U>
    LinealAllocator& operator = (const LinealAllocator<U>&) noexcept;

    ItemType*   allocate(std::size_t n);
    void        deallocate(ItemType* ptr, std::size_t) noexcept;
    void        reset() noexcept;

private:
    enum { MAX_CAP_ARENA = CAP_ARENA };
    static constexpr std::size_t ARENA_SIZE = MAX_CAP_ARENA;
    static char m_memory[ARENA_SIZE];
    static std::size_t m_nextPosition;
    std::array<bool, CAP_ARENA / sizeof(ItemType)> m_availableBlocks{};
};

template<class ItemType>
void* operator new (size_t size, LinealAllocator<ItemType>& allocator);

template<class ItemType>
void operator delete(void* ptr, LinealAllocator<ItemType>& allocator) noexcept;

#include "./LinealAllocatorImpl.hpp"

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