/*!
 * \file IteratorTags.hpp
 *
 * \author kfazi
 * \date February 2010
 *
 * Iterator tag structures.
 */

#ifndef COMMON_ITERATOR_TAGS_HPP
#define COMMON_ITERATOR_TAGS_HPP

#include "../Internal.hpp"

namespace Common
{

/*!
 * \struct IteratorTag
 * \param ValueBaseType Base type of contained data.
 * \param PointerBaseType Pointer type of contained data.
 * \param ReferenceBaseType Reference type of contained data.
 * \headerfile
 * \brief A base iterator tag.
 *
 *
 * Every iterator have to inherit from this structure.
 * - Can be copied and copy-constructed.
 * - Can be incremented.
 *
 * \author kfazi
 * \date February 2010
 */
template<typename ValueBaseType, typename PointerBaseType, typename ReferenceBaseType>
	struct IteratorTag
{
	typedef ValueBaseType ValueType; /*!< Value type. */
	typedef PointerBaseType Pointer; /*!< Pointer type. */
	typedef const PointerBaseType ConstPointer; /*!< Constant pointer type. */
	typedef ReferenceBaseType Reference; /*!< Reference type. */
	//typedef const ReferenceBaseType ConstReference;
};

/*!
 * \struct InputIteratorTag
 * \param ValueType Base type of contained data.
 * \param Pointer Pointer type of contained data.
 * \param Reference Reference type of contained data.
 * \headerfile
 * \brief An input iterator tag.
 *
 *
 * Every input iterator have to inherit from this structure.
 * - Can be copied and copy-constructed.
 * - Can be incremented.
 * - Accepts equality/inequality comparisons.
 * - Can be dereferenced as an rvalue.
 *
 * \author kfazi
 * \date February 2010
 */
template<typename ValueType, typename Pointer, typename Reference> struct InputIteratorTag :
	IteratorTag<ValueType, Pointer, Reference>
{
};

/*!
 * \struct OutputIteratorTag
 * \param ValueType Base type of contained data.
 * \param Pointer Pointer type of contained data.
 * \param Reference Reference type of contained data.
 * \headerfile
 * \brief An output iterator tag.
 *
 *
 * Every output iterator have to inherit from this structure.
 * - Can be copied and copy-constructed.
 * - Can be incremented.
 * - Can be dereferenced to be the left side of an assignment operation.
 *
 * \author kfazi
 * \date February 2010
 */
template<typename ValueType, typename Pointer, typename Reference> struct OutputIteratorTag :
	IteratorTag<ValueType, Pointer, Reference>
{
};

/*!
 * \struct ForwardIteratorTag
 * \param ValueType Base type of contained data.
 * \param Pointer Pointer type of contained data.
 * \param Reference Reference type of contained data.
 * \headerfile
 * \brief A forward iterator tag.
 *
 *
 * Every forward iterator have to inherit from this structure.
 * - Can be copied and copy-constructed.
 * - Can be incremented.
 * - Accepts equality/inequality comparisons.
 * - Can be dereferenced as an rvalue.
 * - Can be default-constructed.
 *
 * \author kfazi
 * \date February 2010
 */
template<typename ValueType, typename Pointer, typename Reference> struct ForwardIteratorTag :
	InputIteratorTag<ValueType, Pointer, Reference>
{
};

/*!
 * \struct BidirectionalIteratorTag
 * \param ValueType Base type of contained data.
 * \param Pointer Pointer type of contained data.
 * \param Reference Reference type of contained data.
 * \headerfile
 * \brief A bidirectional iterator tag.
 *
 *
 * Every bidirectional iterator have to inherit from this structure.
 * - Can be copied and copy-constructed.
 * - Can be incremented.
 * - Accepts equality/inequality comparisons.
 * - Can be dereferenced as an rvalue.
 * - Can be default-constructed.
 * - Can be decremented.
 *
 * \author kfazi
 * \date February 2010
 */
template<typename ValueType, typename Pointer, typename Reference> struct BidirectionalIteratorTag :
	ForwardIteratorTag<ValueType, Pointer, Reference>
{
};

/*!
 * \struct RandomAccessIteratorTag
 * \param ValueType Base type of contained data.
 * \param Pointer Pointer type of contained data.
 * \param Reference Reference type of contained data.
 * \headerfile
 * \brief A random access iterator tag.
 *
 *
 * Every random access iterator have to inherit from this structure.
 * - Can be copied and copy-constructed.
 * - Can be incremented.
 * - Accepts equality/inequality comparisons.
 * - Can be dereferenced as an rvalue.
 * - Can be default-constructed.
 * - Can be decremented.
 * - Supports arithmetic operators + and -.
 * - Supports inequality comparisons (< and >) between iterators.
 * - Supports compound assignment operations +=, -=, <= and >=.
 * - Supports offset dereference operator ([]).
 *
 * \author kfazi
 * \date February 2010
 */
template<typename ValueType, typename Pointer, typename Reference> struct RandomAccessIteratorTag :
	BidirectionalIteratorTag<ValueType, Pointer, Reference>
{
};

}

#endif /* COMMON_ITERATOR_TAGS_HPP */

/* EOF */
