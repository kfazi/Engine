#ifndef COMMON_DEFAULT_ALLOCATOR_HPP
#define COMMON_DEFAULT_ALLOCATOR_HPP

#include "../Internal.hpp"
#include "new.hpp"

template<typename Type> class DefaultAllocator
{
	public:
		typedef Type* Pointer;
		typedef const Type* ConstPointer;
		typedef Type& Reference;
		typedef const Type& ConstReference;

		Pointer Allocate(size_t amount)
		{
			return ::operator new(amount * sizeof(Type));
		}

		void Deallocate(Pointer address)
		{
			::operator delete address;
		}

		void Construct(Pointer address, ConstReference data)
		{ 
			new(address) Type(data); 
		}

		void Destroy(Pointer address)
		{
			address->~Type();
		}
};

#endif /* COMMON_DEFAULT_ALLOCATOR_HPP */

/* EOF */
