/*
* TODO: Create standalone headers
* NOTE: This is a demonstration purpose type of class
* it may be unstable, it might even not work
*/


#include "Memory.hpp"

#include <cstdlib>

namespace GeniEngine
{
	struct MemoryHead
	{
		size_t size;
	};

	class DefaultHeapAllocator : public Allocator
	{
	public:
		DefaultHeapAllocator() {}
		~DefaultHeapAllocator() {}

		virtual void* allocate(size_t size, size_t align = 4) override
		{
			// Calculate proper allocation size to include
			// allocation size, alignment, and the size of the memory header
			const size_t total = size + align + sizeof(MemoryHead);

			// Keep track of memory block header
			MemoryHead* head = static_cast<MemoryHead*>(malloc(total));
			head->size = total;

			// Keep track of actual memory data
			void* data = forceAlign(head + 1, align);

			// Fill memory
			// Set header size and pad end of data
			size_t* p = reinterpret_cast<size_t*>(head + 1);
			while (p != data)
			{
				// Max size
				*p++ = static_cast<size_t>(-1);
			}

			allocated_bytes_ += total;
			++num_allocations_;

			return data;
		}

		virtual void deallocate(void* ptr) override
		{
			if (!ptr)
				return;

			MemoryHead* head = locateMemoryHead(ptr);
			allocated_bytes_ -= head->size;
			--num_allocations_;
			free(head);
		}

		virtual size_t getAllocatedSize(void* ptr) override
		{
			MemoryHead* head = locateMemoryHead(ptr);
			return head->size;
		}

		virtual size_t getNumAllocatedBytes() override
		{
			return allocated_bytes_;
		}

	private:
		inline MemoryHead* locateMemoryHead(void* ptr)
		{
			size_t* addr = reinterpret_cast<size_t*>(ptr);
			--addr;

			while (*addr == static_cast<size_t>(-1))
			{
				--addr;
			}

			return reinterpret_cast<MemoryHead*>(addr);
		}
		size_t allocated_bytes_;
		unsigned num_allocations_;

	};

	const size_t defaultHeapAllocatorSize = sizeof(DefaultHeapAllocator);
	
	// Increment per-byte, otherwise use c-style void ptr
	unsigned buffer[defaultHeapAllocatorSize];

	DefaultHeapAllocator* defaultHeapAllocator = nullptr;

	Allocator& defaultAllocator()
	{
		return *defaultHeapAllocator;
	}

	namespace Memory
	{
		void init()
		{
			// For being able to include different allocators
			// TODO: Add different allocators
			unsigned* ptr = buffer;
			defaultHeapAllocator = new (ptr)DefaultHeapAllocator();
		}

		void shutdown()
		{
			defaultHeapAllocator->~DefaultHeapAllocator();
			defaultHeapAllocator = nullptr;
		}
	}
}