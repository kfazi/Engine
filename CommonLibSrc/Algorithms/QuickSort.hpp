#ifndef COMMON_QUICK_SORT_HPP
#define COMMON_QUICK_SORT_HPP

#include "../Internal.hpp"
#include "Swap.hpp"

namespace Common
{

template<class CRange> void QuickSortInternal(CRange cRange, size_t iStart, size_t iEnd)
{
	size_t iLeft = iStart;
	size_t iRight = iEnd;
	size_t iPivot = (iLeft + iRight) / 2;
	/* Partition */
	while (iLeft <= iRight)
	{
		while (cRange[iLeft] < cRange[iPivot] && iLeft < iEnd)
			iLeft++;
		while (cRange[iRight] > cRange[iPivot] && iRight > iStart)
			iRight--;
		if (iLeft <= iRight)
		{
			Swap(cRange[iLeft], cRange[iRight]);
			if (iLeft < iEnd)
				iLeft++;
			if (iRight > iStart)
				iRight--;
		}
	}
	/* Recursion */
	if (iStart < iRight)
		QuickSortInternal(cRange, iStart, iRight);
	if (iLeft < iEnd)
		QuickSortInternal(cRange, iLeft, iEnd);
}

template<class CRange, class CPredicate> void QuickSortInternal(CRange cRange, size_t iStart, size_t iEnd, CPredicate cPredicate)
{
	size_t iLeft = iStart;
	size_t iRight = iEnd;
	size_t iPivot = (iLeft + iRight) / 2;
	/* Partition */
	while (iLeft <= iRight)
	{
		while (cRange[iLeft] < cRange[iPivot] && iLeft < iEnd)
			iLeft++;
		while (cRange[iRight] > cRange[iPivot] && iRight > iStart)
			iRight--;
		if (cPredicate(iLeft, iRight))
		{
			Swap(cRange[iLeft], cRange[iRight]);
			if (iLeft < iEnd)
				iLeft++;
			if (iRight > iStart)
				iRight--;
		}
	}
	/* Recursion */
	if (iStart < iRight)
		QuickSortInternal(cRange, iStart, iRight, cPredicate);
	if (iLeft < iEnd)
		QuickSortInternal(cRange, iLeft, iEnd, cPredicate);
}

template<class CRange> void QuickSort(CRange cRange)
{
	QuickSortInternal(cRange, 0, cRange.GetLength() - 1);
}

template<class CRange, class CPredicate> void QuickSort(CRange cRange)
{
	QuickSortInternal(cRange, 0, cRange.GetLength() - 1, CPredicate);
}

}

#endif /* COMMON_QUICK_SORT_HPP */

/* EOF */
