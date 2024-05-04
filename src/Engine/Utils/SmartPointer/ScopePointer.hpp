#pragma once

template <typename Type, bool doFree>
class SafeUniquePtr {
public:
    explicit SafeUniquePtr(Type* ptr = nullptr);
    SafeUniquePtr(const SafeUniquePtr&) = delete;
    SafeUniquePtr(SafeUniquePtr&& other) noexcept;

    ~SafeUniquePtr();

    SafeUniquePtr& operator = (const SafeUniquePtr&) = delete;
    SafeUniquePtr& operator = (SafeUniquePtr&& other)       noexcept;
    Type* get()                                       const noexcept;
    Type& operator * ()                               const noexcept;
    Type* operator -> ()                              const noexcept;
    explicit operator bool()                          const noexcept;

private:
    Type* ptr_;
    bool shouldDelete = doFree;
};

#include "./ScopePointerImpl.hpp"

template <typename Type, bool doFree = false>
using ScopePtr = SafeUniquePtr<Type, doFree>;