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