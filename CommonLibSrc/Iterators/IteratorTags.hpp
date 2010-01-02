#ifndef COMMON_ITERATOR_TAGS_HPP
#define COMMON_ITERATOR_TAGS_HPP

#include "../Internal.hpp"

namespace Common
{

template<typename ValueType, typename Pointer, typename Reference> struct IteratorTag
{
	typedef ValueType ValueType;
	typedef Pointer Pointer;
	typedef Reference Reference;
/*	typename iterator_traits<_Iterator>::iterator_category,
	typename iterator_traits<_Iterator>::value_type,
	typename iterator_traits<_Iterator>::difference_type,
	typename iterator_traits<_Iterator>::pointer,
	typename iterator_traits<_Iterator>::reference*/
	/**
	 * Any iterator.
	 * - Can be copied and copy-constructed.
	 * - Can be incremented.
	 */
};

template<typename ValueType, typename Pointer, typename Reference> struct InputIteratorTag : IteratorTag<ValueType, Pointer, Reference>
{
	/**
	 * - Accepts equality/inequality comparisons.
	 * - Can be dereferenced as an rvalue.
	 */
};

template<typename ValueType, typename Pointer, typename Reference> struct OutputIteratorTag : IteratorTag<ValueType, Pointer, Reference>
{
	/**
	 * - Can be dereferenced to be the left side of an assignment operation.
	 */
};

template<typename ValueType, typename Pointer, typename Reference> struct ForwardIteratorTag : InputIteratorTag<ValueType, Pointer, Reference>
{
	/**
	 * - Can be default-constructed.
	 */
};

template<typename ValueType, typename Pointer, typename Reference> struct BidirectionalIteratorTag : ForwardIteratorTag<ValueType, Pointer, Reference>
{
	/**
	 * - Can be decremented.
	 */
};

template<typename ValueType, typename Pointer, typename Reference> struct RandomAccessIteratorTag : BidirectionalIteratorTag<ValueType, Pointer, Reference>
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
