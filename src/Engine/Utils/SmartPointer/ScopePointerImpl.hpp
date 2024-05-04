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