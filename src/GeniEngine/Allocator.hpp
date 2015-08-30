#pragma once

#include <new>
#include <utility>

namespace GeniEngine
{
	class Allocator
	{
	public:
		Allocator(){}
		virtual ~Allocator() {}

		virtual void* allocate(size_t size, size_t align = 4) = 0;
		virtual void deallocate(void* p) = 0;
		virtual size_t allocatedSize(void* p) = 0;

		template<typename T, typename... Args>
		T* makeNew(Args&&... args)
		{
			return new (allocate(sizeof(T), __alignof(T))) T{std::forward<Args>(args)...};
		}

		template<typename T>
		void makeDelete(T* ptr)
		{
			if (ptr)
			{
				ptr->~T();
				deallocate(ptr);
			}
		}

	private:
		Allocator(const Allocator&) = delete;
		Allocator& operator=(const Allocator&) = delete;

	};
}