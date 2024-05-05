/**
 * @author: Kevin Daniel Taylor
 * @license: MIT License
 * 
 * - For more information about the license, please see the end of the file.
 * - Copyright (c) 2024 Kevin Daniel Taylor
 */

#ifndef SCOPEPOINTER_HPP
#define SCOPEPOINTER_HPP

#include "./ScopePointer.hpp"

template <typename Type, bool doFree>
SafeUniquePtr<Type, doFree>::SafeUniquePtr(Type* ptr) : ptr_(ptr) {}

template <typename Type, bool doFree>
SafeUniquePtr<Type, doFree>::~SafeUniquePtr() {
    if (ptr_ && shouldDelete) {
        delete ptr_;
    }
    ptr_ = nullptr;
}

template <typename Type, bool doFree>
SafeUniquePtr<Type, doFree>::SafeUniquePtr(SafeUniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

template <typename Type, bool doFree>
SafeUniquePtr<Type, doFree>& SafeUniquePtr<Type, doFree>::operator=(SafeUniquePtr&& other) noexcept {
    if (this != &other) {
        if (shouldDelete) {
            delete ptr_;
        }
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

template <typename Type, bool doFree>
Type* SafeUniquePtr<Type, doFree>::get() const noexcept {
    return ptr_;
}

template <typename Type, bool doFree>
Type& SafeUniquePtr<Type, doFree>::operator*() const noexcept {
    return *ptr_;
}

template <typename Type, bool doFree>
Type* SafeUniquePtr<Type, doFree>::operator->() const noexcept {
    return ptr_;
}

template <typename Type, bool doFree>
SafeUniquePtr<Type, doFree>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

#endif // SCOPEPOINTER_HPP

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