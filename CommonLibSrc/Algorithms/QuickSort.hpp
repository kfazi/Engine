#ifndef COMMON_QUICK_SORT_HPP
#define COMMON_QUICK_SORT_HPP

#include "../Internal.hpp"
#include "Swap.hpp"

namespace Common
{

template<class CType> void QuickSort(CType cFirst, CType cLast)
{
	CType cLeft = cFirst;
	CType cRight = cLast;
	CType cPivot = (cLeft + cRight) / 2;
	/* Partition */
	while (cLeft <= cRight)
	{
		while (*cLeft < *cPivot)
			cLeft++;
		while (*cRight > *cPivot)
			cRight--;
		if (cLeft <= cRight)
		{
			Swap(*cLeft, *cRight);
			cLeft++;
			cRight--;
		}
	}
	/* recursion */
	if (cFirst < cRight)
		QuickSort(cFirst, cRight);
	if (cLeft < cLast)
		QuickSort(cLeft, cLast);
}

template<class CType, class CPredicate> void QuickSort(CType cFirst, CType cLast, CPredicate cPredicate)
{
	CType cLeft = cFirst;
	CType cRight = cLast;
	CType cPivot = (cLeft + cRight) / 2;
	/* Partition */
	while (cLeft <= cRight)
	{
		while (cPredicate(*cLeft, *cPivot))
			cLeft++;
		while (cPredicate(*cPivot, *cRight))
			cRight--;
		if (cLeft <= cRight)
		{
			Swap(*cLeft, *cRight);
			cLeft++;
			cRight--;
		}
	}
	/* recursion */
	if (cFirst < cRight)
		QuickSort(cFirst, cRight);
	if (cLeft < cLast)
		QuickSort(cLeft, cLast);
}

}

#endif /* COMMON_QUICK_SORT_HPP */

/* EOF */
