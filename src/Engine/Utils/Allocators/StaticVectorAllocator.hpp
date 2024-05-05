/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#pragma once

#include <limits>
#include <memory>
#include <typeinfo>

/**
 * Compatible with std::vector
 * Only takes 2 parameters in the template arguments
 *
 *  @param typename - T type
 *  @param size_t   - Capacity
 */
template <typename T, std::size_t Capacity> 
class StaticVectorAllocator {
public:
    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    template <typename U> struct rebind {
        using other = StaticVectorAllocator<U, Capacity>;
    };

    StaticVectorAllocator() noexcept {}

    template <typename U>
    StaticVectorAllocator(const StaticVectorAllocator<U, Capacity>&) noexcept {}

    pointer allocate(size_type n) {
        if (n > Capacity) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<pointer> (&storage);
    }

    void deallocate(pointer p, size_type n) noexcept {}

    size_type max_size() const noexcept {
        return Capacity;
    }

private:
    alignas (alignof (T)) unsigned char storage[sizeof(T) * Capacity];
};

template <typename T, std::size_t Capacity>
bool operator == (const StaticVectorAllocator<T, Capacity>&, const StaticVectorAllocator<T, Capacity>&) noexcept {
    return true;
}

template <typename T, std::size_t Capacity> 
bool operator != (const StaticVectorAllocator<T, Capacity>&, const StaticVectorAllocator<T, Capacity>&) noexcept {
    return false;
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