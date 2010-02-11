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
/*		CType& PopFront()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *m_pBegin++;
		}

		CType& Back()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *m_pEnd;
		}

		CType& PopBack()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *m_pEnd--;
		}

		CType& At(unsigned int iIndex)
		{
			Assert(m_pBegin + iIndex <= m_pEnd, "Index out of range");
			return *(m_pBegin + iIndex);
		}

		CType& operator[] (unsigned int iIndex)
		{
			return At(iIndex);
		}*/
};

}

#endif /* COMMON_RANGE_HPP */

/* EOF */
