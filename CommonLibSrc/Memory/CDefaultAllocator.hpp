#ifndef COMMON_DEFAULT_ALLOCATOR_HPP
#define COMMON_DEFAULT_ALLOCATOR_HPP

#include "../Internal.hpp"
#include "new.hpp"

template<typename tType> class CDefaultAllocator
{
	public:
		tType* Allocate()
		{
			return new tType;
		}
};

#endif /* COMMON_DEFAULT_ALLOCATOR_HPP */

/* EOF */
