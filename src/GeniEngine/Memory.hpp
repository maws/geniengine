#pragma once

#include "Allocator.hpp"

namespace GeniEngine
{
	Allocator& defaultAllocator();

	namespace Memory
	{
		void init();
		void shutdown();
	}
	

	/// \brief Make sure the pointer has proper alignment
	/// if not, align the ptr using simple ptr arithmetics
	inline void* forceAlign(void* ptr, size_t alignment)
	{
		unsigned addr = reinterpret_cast<unsigned>(ptr);
		const size_t offset = addr % alignment;
		if (offset)
		{
			addr += static_cast<unsigned>((alignment - offset));
		}
		return reinterpret_cast<void*>(addr);
	}
}