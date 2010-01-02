#ifndef COMMON_ITERATOR_TAGS_HPP
#define COMMON_ITERATOR_TAGS_HPP

#include "../Internal.hpp"

namespace Common
{

template<typename ValueBaseType, typename PointerBaseType, typename ReferenceBaseType> struct IteratorTag
{
	typedef ValueBaseType ValueType;
	typedef PointerBaseType Pointer;
	typedef const PointerBaseType ConstPointer;
	typedef ReferenceBaseType Reference;
	//typedef const ReferenceBaseType ConstReference;
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
