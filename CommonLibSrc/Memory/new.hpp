#ifndef COMMON_MEMORY_NEW_HPP
#define COMMON_MEMORY_NEW_HPP

#include <new>
#include <cstdlib>

inline void* operator new(size_t iSize)
{
	return malloc(iSize);
}

inline void operator delete(void* pAddress)
{
	free(pAddress);
}

inline void* operator new[](size_t iSize)
{
	return malloc(iSize);
}

inline void operator delete[](void* pAddress)
{
	free(pAddress);
}

#endif /* COMMON_MEMORY_NEW_HPP */

/* EOF */
