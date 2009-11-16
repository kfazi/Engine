#ifndef COMMON_MEMORY_RANGE_HPP
#define COMMON_MEMORY_RANGE_HPP

#include "../Internal.hpp"

namespace Common
{

template<class CType> class CMemoryRange
{
	private:
		CType* m_pBegin;
		CType* m_pEnd;

	public:
		template<size_t iArraySize> CMemoryRange(CType (&aArray)[iArraySize])
		{
			m_pBegin = aArray;
			m_pEnd = aArray + iArraySize;
		}

		CMemoryRange(CType* pBegin, CType* pEnd)
		{
			Assert(pBegin <= pEnd, "Begin is after end");
			m_pBegin = pBegin;
			m_pEnd = pEnd;
		}

		bool IsEmpty() const
		{
			return m_pBegin >= m_pEnd;
		}

		unsigned int GetLength() const
		{
			return m_pEnd - m_pBegin;
		}

		CType& Front()
		{
			Assert(!IsEmpty(), "Range is empty");
			return *m_pBegin;
		}

		CType& PopFront()
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
		}
};

template<class CType, size_t iArraySize> CMemoryRange<CType> CreateRange(CType (&aArray)[iArraySize])
{
	return CMemoryRange<CType>(aArray, aArray + iArraySize);
}

template<class CType, size_t iArraySize> CMemoryRange<CType> CreateRange(CType* pBegin, CType* pEnd)
{
	return CMemoryRange<CType>(pBegin, pEnd);
}

}

#endif /* COMMON_MEMORY_RANGE_HPP */

/* EOF */
