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