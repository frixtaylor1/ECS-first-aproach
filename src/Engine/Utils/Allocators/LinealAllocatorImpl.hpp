/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#ifndef LINEALALLOCATORIMPL_HPP
#define LINEALALLOCATORIMPL_HPP

#include "./LinealAllocator.hpp"

template<class ItemType, size_t CAP_ARENA>
LinealAllocator<ItemType, CAP_ARENA>::LinealAllocator() noexcept = default;

template<class ItemType, size_t CAP_ARENA>
LinealAllocator<ItemType, CAP_ARENA>::~LinealAllocator() noexcept = default;

template<class ItemType, size_t CAP_ARENA>
template<typename U>
LinealAllocator<ItemType, CAP_ARENA>::LinealAllocator(const LinealAllocator<U>&) noexcept {}

template<class ItemType, size_t CAP_ARENA>
template<typename U>
LinealAllocator<ItemType, CAP_ARENA>& LinealAllocator<ItemType, CAP_ARENA>::operator = (const LinealAllocator<U>&) noexcept {
    return *this;
}

template<class ItemType, size_t CAP_ARENA>
ItemType* LinealAllocator<ItemType, CAP_ARENA>::allocate(std::size_t n) {
    if (n != 1) {
        return nullptr;
    }
    if (m_nextPosition + sizeof(ItemType) > ARENA_SIZE) {
        return nullptr;
    }
    void* ptr = &m_memory[m_nextPosition];
    m_nextPosition += sizeof(ItemType);
    return static_cast<ItemType*>(ptr);
}

template<class ItemType, size_t CAP_ARENA>
void LinealAllocator<ItemType, CAP_ARENA>::deallocate(ItemType* ptr, std::size_t) noexcept {
    if (reinterpret_cast<char*>(ptr) == &m_memory[m_nextPosition - sizeof(ItemType)]) {
        /* calculate the index of the freed block. */
        std::size_t index = (m_nextPosition - sizeof(ItemType)) / sizeof(ItemType);
        /*  set this block as free. */
        m_availableBlocks[index] = true;
        /* update the next position to be allocated. */
        if (index * sizeof(ItemType) < m_nextPosition) {
            m_nextPosition = index * sizeof(ItemType);
        }
    }
}

template<class ItemType, size_t CAP_ARENA>
void LinealAllocator<ItemType, CAP_ARENA>::reset() noexcept {
    m_nextPosition = 0;
}

template<class ItemType, size_t CAP_ARENA>
char LinealAllocator<ItemType, CAP_ARENA>::m_memory[LinealAllocator<ItemType, CAP_ARENA>::ARENA_SIZE];

template<class ItemType, size_t CAP_ARENA>
std::size_t LinealAllocator<ItemType, CAP_ARENA>::m_nextPosition = 0;

template<class ItemType>
void* operator new (size_t size, LinealAllocator<ItemType>& allocator) {
    return allocator.allocate(1);
}
template<class ItemType>
void operator delete(void* ptr, LinealAllocator<ItemType>& allocator) noexcept {
    allocator.deallocate(static_cast<ItemType*>(ptr), 1);
}

#endif // LINEALALLOCATORIMPL_HPP

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