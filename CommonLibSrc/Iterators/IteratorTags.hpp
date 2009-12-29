#ifndef COMMON_ITERATOR_TAGS_HPP
#define COMMON_ITERATOR_TAGS_HPP

#include "../Internal.hpp"

namespace Common
{

struct IteratorTag
{
	/**
	 * Any iterator.
	 * - Can be copied and copy-constructed.
	 * - Can be incremented.
	 */
};

struct InputIteratorTag : IteratorTag
{
	/**
	 * - Accepts equality/inequality comparisons.
	 * - Can be dereferenced as an rvalue.
	 */
};

struct OutputIteratorTag : IteratorTag
{
	/**
	 * - Can be dereferenced to be the left side of an assignment operation.
	 */
};

struct ForwardIteratorTag : InputIteratorTag, OutputIteratorTag
{
	/**
	 * - Can be default-constructed.
	 */
};

struct BidirectionalIteratorTag : ForwardIteratorTag
{
	/**
	 * - Can be decremented.
	 */
};

struct RandomAccessIteratorTag : BidirectionalIteratorTag
{
	/**
	 * - Supports arithmetic operators + and -.
	 * - Supports inequality comparisons (< and >) between iterators.
	 * - Supports compound assignment operations +=, -=, <= and >=.
	 * - Supports offset dereference operator ([]).
	 */
};

}

#endif /* COMMON_ITERATOR_TAGS_HPP */

/* EOF */
