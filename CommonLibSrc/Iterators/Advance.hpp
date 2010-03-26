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

template<typename ValueType, typename Pointer, typename Reference>
void Advance(InputIteratorTag<ValueType, Pointer, Reference>& iterator, size_t distance)
{
	while (distance--)
		++iterator;
}

template<typename ValueType, typename Pointer, typename Reference>
void Advance(BidirectionalIteratorTag<ValueType, Pointer, Reference>& iterator, size_t distance)
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

template<typename ValueType, typename Pointer, typename Reference>
void Advance(RandomAccessIteratorTag<ValueType, Pointer, Reference>& iterator, size_t distance)
{
	iterator += distance;
}

}

#endif /* COMMON_ADVANCE_HPP */

/* EOF */
