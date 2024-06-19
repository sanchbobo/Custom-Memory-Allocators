#ifndef STL_ALLOCATOR_ADAPTER_HPP
#define STL_ALLOCATOR_ADAPTER_HPP

#include <cstddef>
#include <limits>
#include <memory>
#include <type_traits>

template<typename T, typename Allocator>
class STLAllocatorAdapter {
public:
    using value_type    = T;
    using pointer       = T*;
    using const_pointer = const T*;
    using size_type     = std::size_t;
    using difference_type = std::ptrdiff_t;

    template<typename U>
    struct rebind {
        using other = STLAllocatorAdapter<U, Allocator>;
    };

    explicit STLAllocatorAdapter(Allocator* allocator = nullptr) noexcept : allocator(allocator) {}

    STLAllocatorAdapter(const STLAllocatorAdapter& other) noexcept = default;

    template<typename U>
    STLAllocatorAdapter(const STLAllocatorAdapter<U, Allocator>& other) noexcept : allocator(other.allocator) {}

    ~STLAllocatorAdapter() noexcept = default;

    STLAllocatorAdapter& operator=(const STLAllocatorAdapter&) = delete; // Non-Assignable

    T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_alloc();

        return static_cast<T*>(allocator->Allocate(n * sizeof(T), alignof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        allocator->Free(p);
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new((void*)p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    bool operator==(const STLAllocatorAdapter& other) const noexcept {
        return allocator == other.allocator;
    }

    bool operator!=(const STLAllocatorAdapter& other) const noexcept {
        return !(*this == other);
    }

    Allocator* get_allocator() const noexcept {
        return allocator;
    }

private:
    Allocator* allocator;
};

#endif // STL_ALLOCATOR_ADAPTER_HPP
