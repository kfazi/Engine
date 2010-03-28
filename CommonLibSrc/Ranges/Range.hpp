#ifndef COMMON_RANGE_HPP
#define COMMON_RANGE_HPP

#include "../Internal.hpp"

namespace Common
{

template<class IteratorType> class Range
{
	private:
		IteratorType mBegin;
		IteratorType mEnd;

	public:
		typedef typename IteratorType::ValueType ValueType;
		typedef typename IteratorType::Reference Reference;
		typedef typename IteratorType::Pointer Pointer;

		Range(const IteratorType& begin, const IteratorType& end)
		{
			mBegin = begin;
			mEnd = end;
		}

		bool IsEmpty() const
		{
			return mBegin == mEnd;
		}

		Reference Front()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *mBegin;
		}

		Reference Front() const
		{
			Assert(!IsEmpty(), "Range is empty");
			return *mBegin;
		}
/*		Type& PopFront()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *mBegin++;
		}

		Type& Back()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *mEnd;
		}

		Type& PopBack()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *mEnd--;
		}

		Type& At(unsigned int iIndex)
		{
			Assert(mBegin + iIndex <= mEnd, "Index out of range");
			return *(mBegin + iIndex);
		}

		Type& operator[] (unsigned int iIndex)
		{
			return At(iIndex);
		}*/
};

}

#endif /* COMMON_RANGE_HPP */

/* EOF */
