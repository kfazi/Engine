/*!
 * \file Pair.hpp
 *
 * \author kfazi
 * \date March 2010
 *
 * \link Common::Pair Pair\endlink structure.
 */

#ifndef COMMON_PAIR_HPP
#define COMMON_PAIR_HPP

#include "../Internal.hpp"

namespace Common
{

/*!
 * \class Pair
 * \param FirstType Type of first data.
 * \param SecondType Type of second data.
 * \headerfile
 * \brief A pair structure.
 *
 * \author kfazi
 * \date March 2010
 */
template<class FirstType, class SecondType> struct Pair
{
	typedef Pair<FirstType, SecondType> MyType; /*!< Type of this pair. */

	/*!
	 * Constructor.
	 */
	Pair()
	{
	}

	/*!
	 * Constructor.
	 *
	 * \param[in] first First value in pair.
	 * \param[in] second Second value in pair.
	 */
	Pair(const FirstType& first, const SecondType& second) : first(first), second(second)
	{
	}

	/*!
	 * Copy constructor.
	 *
	 * \param[in] pair Pair to copy first and second value from.
	 */
	Pair(const MyType& pair) : first(pair.first), second(pair.second)
	{
	}

	/*!
	 * Assignment operator.
	 *
	 * \param[in] pair Pair to copy first and second value from.
	 * \return Actual pair.
	 */
	MyType& operator= (const Pair& pair)
	{
		first = pair.first;
		second = pair.second;
		return *this;
	}

	/*!
	 * Comparison operator.
	 *
	 * \param[in] pair A pair to compare to.
	 * \return True if pairs are equal.
	 */
	bool operator== (const MyType& pair)
	{
		return first == pair.first && second == pair.second;
	}

	/*!
	 * Less than operator.
	 *
	 * It uses lexicographic comparison: the return value is true if the first element of first pair
	 * is less than the first element of second pair, and false if the first element of second pair is
	 * less than the first element of first pair. If neither of these is the case, then operator<
	 * returns the result of comparing the second elements of first and second pair.
	 *
	 * \param[in] iterator A pair to compare to.
	 * \return True if first pair is smaller than the second one.
	 */
	bool operator< (const MyType& pair)
	{
		if (first == pair.first)
			return second < pair.second;
		return first < pair.first;
	}

	FirstType first; /*!< First element. */
	SecondType second; /*!< Second element. */
};

template<class FirstType,class SecondType> Pair<FirstType, SecondType>
	MakePair(FirstType first, SecondType second)
{
	return Pair<FirstType, SecondType>(first, second);
}

}

#endif /* COMMON_PAIR_HPP */

/* EOF */
