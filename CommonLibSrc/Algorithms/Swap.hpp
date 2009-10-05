#ifndef COMMON_SWAP_HPP
#define COMMON_SWAP_HPP

#include "../Internal.hpp"

namespace Common
{

template<class CType> void Swap(CType &cFirst, CType &cSecond)
{
	CType cTemp = cFirst;
	cFirst = cSecond;
	cSecond = cTemp;
}

template<class CType> void SwapRange(CType cFirst, CType cLast)
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
