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
class StaticAllocator {
public:
    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    template <typename U> struct rebind {
        using other = StaticAllocator<U, Capacity>;
    };

    StaticAllocator() noexcept {}

    template <typename U>
    StaticAllocator(const StaticAllocator<U, Capacity>&) noexcept {}

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
bool operator == (const StaticAllocator<T, Capacity>&, const StaticAllocator<T, Capacity>&) noexcept {
    return true;
}

template <typename T, std::size_t Capacity> 
bool operator != (const StaticAllocator<T, Capacity>&, const StaticAllocator<T, Capacity>&) noexcept {
    return false;
}