#pragma once

#include "./ScopePointer.hpp"

template <typename Type>
SafeUniquePtr<Type>::SafeUniquePtr(Type* ptr) : ptr_(ptr) {}

template <typename Type>
SafeUniquePtr<Type>::~SafeUniquePtr() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename Type>
SafeUniquePtr<Type>::SafeUniquePtr(SafeUniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

template <typename Type>
SafeUniquePtr<Type>& SafeUniquePtr<Type>::operator=(SafeUniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

template <typename Type>
Type* SafeUniquePtr<Type>::get() const noexcept {
    return ptr_;
}

template <typename Type>
Type& SafeUniquePtr<Type>::operator*() const noexcept {
    return *ptr_;
}

template <typename Type>
Type* SafeUniquePtr<Type>::operator->() const noexcept {
    return ptr_;
}

template <typename Type>
SafeUniquePtr<Type>::operator bool() const noexcept {
    return ptr_ != nullptr;
}
