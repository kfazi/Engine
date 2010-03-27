/*!
 * \file Advance.hpp
 *
 * \author kfazi
 * \date March 2010
 *
 * Iterator advance function.
 */

#ifndef COMMON_ADVANCE_HPP
#define COMMON_ADVANCE_HPP

#include "../Internal.hpp"
#include "IteratorTags.hpp"

namespace Common
{

template<class IteratorType, typename ValueType, typename Pointer, typename Reference>
void Advance(IteratorType& iterator, size_t distance, InputIteratorTag<ValueType, Pointer,
	Reference>&)
{
	while (distance--)
		++iterator;
}

template<class IteratorType, typename ValueType, typename Pointer, typename Reference>
void Advance(IteratorType& iterator, size_t distance, BidirectionalIteratorTag<ValueType, Pointer,
	Reference>&)
{
	if (distance > 0)
	{
		while (distance--)
			++iterator;
	}
	else
	{
		while (distance++)
			--iterator;
	}
}

template<class IteratorType, typename ValueType, typename Pointer, typename Reference>
void Advance(IteratorType& iterator, size_t distance, RandomAccessIteratorTag<ValueType, Pointer,
	Reference>&)
{
	iterator += distance;
}

template<class IteratorType>
void Advance(IteratorType& iterator, size_t distance)
{
	Advance(iterator, distance, iterator);
}

}

#endif /* COMMON_ADVANCE_HPP */

/* EOF */
