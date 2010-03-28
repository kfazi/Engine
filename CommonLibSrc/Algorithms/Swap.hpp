#ifndef COMMON_SWAP_HPP
#define COMMON_SWAP_HPP

#include "../Internal.hpp"

namespace Common
{

template<class Type> void Swap(Type& cFirst, Type& cSecond)
{
	Type cTemp = cFirst;
	cFirst = cSecond;
	cSecond = cTemp;
}

template<class Type> void SwapRange(Type cFirst, Type cLast)
{
	if (cFirst < cLast)
		Swap(cFirst, cLast);
	while (cFirst < cLast)
	{
		Swap(*cFirst, *cLast);
		cFirst++;
		cLast--;
	}
}

}

#endif /* COMMON_SWAP_HPP */

/* EOF */
