#include "LinearAllocator.hpp"
#include <utility>
#include <cassert>
#include <new>

LinearAllocator::LinearAllocator(const std::size_t sizeBytes, void* const start) noexcept
:
	Allocator(sizeBytes, start),
	m_current(const_cast<void*>(start))
{

}


LinearAllocator::LinearAllocator(LinearAllocator&& other) noexcept
:
	Allocator(std::move(other)),
	m_current(other.m_current)
{
	other.m_current = nullptr;
}



void LinearAllocator::Clear() noexcept
{
	m_numAllocations = 0;
	m_usedBytes = 0;
	
	m_current = const_cast<void*>(m_start);
}
	
LinearAllocator::~LinearAllocator() noexcept
{
    Clear();
}

LinearAllocator& LinearAllocator::operator=(LinearAllocator&& rhs) noexcept
{
	Allocator::operator=(std::move(rhs));
	m_current = rhs.m_current;
	rhs.m_current = nullptr;
	return *this;
}

std::size_t align_forward_adjustment(const void* current_ptr, std::size_t alignment) {
	std::uintptr_t current_address = reinterpret_cast<std::uintptr_t>(current_ptr);
	std::size_t adjustment = alignment - (current_address % alignment);
	if (adjustment == alignment) return 0; // Already aligned
	return adjustment;
}

inline void* ptr_add(const void* const p, std::uintptr_t alignment)
{
        return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(p) + alignment);
}


void* LinearAllocator::Allocate(const std::size_t& size, const std::uintptr_t& alignment)
{
	std::size_t adjustment = align_forward_adjustment(m_current, alignment);

	if (size + adjustment + m_usedBytes > m_size) {
		throw std::bad_alloc();
	}

	void* alignedAddr = ptr_add(m_current, adjustment);

	m_current = ptr_add(alignedAddr, size);

	m_usedBytes = reinterpret_cast<std::intptr_t>(m_current) - reinterpret_cast<std::intptr_t>(m_start);

	++m_numAllocations;

	return alignedAddr;
}




void LinearAllocator::Free([[maybe_unused]] void* const ptr) noexcept
{

}

void LinearAllocator::Rewind(void* const mark) noexcept
{
	assert(m_current >= mark && m_start <= mark);
	
	m_current = mark;

	m_usedBytes = reinterpret_cast<std::uintptr_t>(m_current) - reinterpret_cast<std::uintptr_t>(m_start);
}



void* LinearAllocator::GetCurrent() const noexcept 
{
	return m_current;
}
