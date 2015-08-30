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

			// Keep track of actual memory data
			void* data = ++head;
			data = forceAlign(data, align);

			// Fill memory
			// Set header size and pad end of data
			head->size = total;
			size_t* p = reinterpret_cast<size_t*>(head + 1);
			while (p < data)
			{
				// Max size
				*p++ = static_cast<size_t>(-1);
			}
			return data;
		}

		virtual void deallocate(void* ptr) override
		{
			if (!ptr)
				return;

			MemoryHead* head = locateMemoryHead(ptr);
			total_size_ = head->size;
			free(head);
		}

		virtual size_t allocatedSize(void* ptr) override
		{
			MemoryHead* head = locateMemoryHead(ptr);
			return head->size;
		}

	private:
		inline MemoryHead* locateMemoryHead(void* ptr)
		{
			size_t* addr = reinterpret_cast<size_t*>(ptr);
			while (*(addr - 1) == static_cast<size_t>(-1))
			{
				--addr;
			}

			return reinterpret_cast<MemoryHead*>(addr - 1);
		}
		size_t total_size_;
	};

	const size_t defaultHeapAllocatorSize = sizeof(DefaultHeapAllocator);
	
	// Increment per-byte, otherwise use c-style void ptr
	unsigned buffer[defaultHeapAllocatorSize];

	DefaultHeapAllocator* defaultHeapAllocator = nullptr;

	Allocator& defaultAllocator()
	{
		return *defaultHeapAllocator;
	}

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