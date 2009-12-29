#ifndef COMMON_DEFAULT_ALLOCATOR_HPP
#define COMMON_DEFAULT_ALLOCATOR_HPP

#include "../Internal.hpp"
#include "new.hpp"

namespace Common
{

template<typename Type> class DefaultAllocator
{
	public:
		typedef Type* Pointer;
		typedef const Type* ConstPointer;
		typedef Type& Reference;
		typedef const Type& ConstReference;

		template<typename NewType> struct Rebind
		{
			typedef DefaultAllocator<NewType> Other;
		};

		static Pointer Allocate(size_t amount)
		{
			return static_cast<Pointer>(::operator new(amount * sizeof(Type)));
		}

		static void Deallocate(Pointer address)
		{
			::operator delete(address);
		}

		static void Construct(Pointer address, ConstReference data)
		{ 
			new(address) Type(data); 
		}

		static void Destroy(ConstPointer address)
		{
			address->~Type();
		}
};

}

#endif /* COMMON_DEFAULT_ALLOCATOR_HPP */

/* EOF */
