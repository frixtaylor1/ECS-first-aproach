#include <typeinfo>
#include <cstddef>

template<class ItemType, size_t CAP_ARENA = 1024>
class LinealAllocator {
public:
    using value_type = ItemType;

    LinealAllocator() noexcept = default;
    ~LinealAllocator() noexcept = default;

    template<typename U>
    LinealAllocator(const LinealAllocator<U>&) noexcept {}

    template<typename U>
    LinealAllocator& operator=(const LinealAllocator<U>&) noexcept { return *this; }

    ItemType* allocate(std::size_t n) {
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

    void deallocate(ItemType* ptr, std::size_t) noexcept {
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

    void reset() noexcept {
        m_nextPosition = 0;
    }

private:
    enum { MAX_CAP_ARENA = CAP_ARENA };
    static constexpr std::size_t ARENA_SIZE = MAX_CAP_ARENA;
    static char m_memory[ARENA_SIZE];
    static std::size_t m_nextPosition;
    std::array<bool, CAP_ARENA / sizeof(ItemType)> m_availableBlocks{};
};

template<class ItemType, size_t CAP_ARENA>
char LinealAllocator<ItemType, CAP_ARENA>::m_memory[LinealAllocator<ItemType, CAP_ARENA>::ARENA_SIZE];

template<class ItemType, size_t CAP_ARENA>
std::size_t LinealAllocator<ItemType,CAP_ARENA>::m_nextPosition = 0;

template<class ItemType>
void* operator new (size_t size, LinealAllocator<ItemType>& allocator) {
    return allocator.allocate(1);
}
template<class ItemType>
void operator delete(void* ptr, LinealAllocator<ItemType>& allocator) noexcept {
    allocator.deallocate(static_cast<ItemType*>(ptr), 1);
}