#ifndef COMMON_FIND_HPP
#define COMMON_FIND_HPP

#include "../Internal.hpp"

namespace Common
{

template<class CRange, typename TType> bool Find(CRange cRange, const TType& tValue, size_t& iIndex)
{
	iIndex = 0;
	while (!cRange.IsEmpty())
	{
		if (cRange.PopFront() == tValue)
			return true;
		iIndex++;
	}
	return false;
}

}

#endif /* COMMON_FIND_HPP */

/* EOF */
