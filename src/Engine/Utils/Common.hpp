#ifndef COMMON_HPP
#define COMMON_HPP

#define interface   struct
#define implements  public
#define extends     public

template <typename Type>
class SafeUniquePtr {
public:
    explicit SafeUniquePtr(Type* ptr = nullptr) : ptr_(ptr) {}

    ~SafeUniquePtr() {
        delete ptr_;
    }

    SafeUniquePtr(const SafeUniquePtr&) = delete;
    SafeUniquePtr& operator = (const SafeUniquePtr&) = delete;

    SafeUniquePtr(SafeUniquePtr&& other) noexcept
        : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    SafeUniquePtr& operator=(SafeUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    Type* get() const noexcept {
        return ptr_;
    }

    Type& operator * () const noexcept {
        return *ptr_;
    }

    Type* operator -> () const noexcept {
        return ptr_;
    }

    explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

private:
    Type* ptr_;
};

template <typename Type>
using ScopePtr = SafeUniquePtr<Type>;

#endif // COMMON_HPP