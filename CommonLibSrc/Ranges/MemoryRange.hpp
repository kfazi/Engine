#ifndef COMMON_MEMORY_RANGE_HPP
#define COMMON_MEMORY_RANGE_HPP

#include "../Internal.hpp"

namespace Common
{

template<class Type> class MemoryRange
{
	private:
		Type* mBegin;
		Type* mEnd;

	public:
		template<size_t ArraySize> MemoryRange(Type (&array)[ArraySize])
		{
			mBegin = array;
			mEnd = array + ArraySize;
		}

		MemoryRange(Type* begin, Type* end)
		{
			Assert(begin <= end, "Begin is after end");
			mBegin = begin;
			mEnd = end;
		}

		bool IsEmpty() const
		{
			return mBegin >= mEnd;
		}

		unsigned int GetLength() const
		{
			return mEnd - mBegin;
		}

		Type& Front()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *mBegin;
		}

		Type& PopFront()
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
		}
};

template<class Type, size_t ArraySize> MemoryRange<Type> CreateRange(Type (&array)[ArraySize])
{
	return MemoryRange<Type>(array, array + ArraySize);
}

template<class Type, size_t ArraySize> MemoryRange<Type> CreateRange(Type* begin, Type* end)
{
	return MemoryRange<Type>(begin, end);
}

}

#endif /* COMMON_MEMORY_RANGE_HPP */

/* EOF */
