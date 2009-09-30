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

}

#endif /* COMMON_SWAP_HPP */

/* EOF */
