#ifndef COMMON_VECTOR_HPP
#define COMMON_VECTOR_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"

namespace Common
{

template<class CType> class CVector
{
	private:
		typedef CVector<CType> TMyType;
		CType* m_pBuffer;
		size_t m_iLength;
		size_t m_iCapacity;

	public:
		class CRange
		{
			private:
				size_t m_iRangeStart;
				size_t m_iRangeLength;
				CVector& m_cVector;

			public:
				CRange(CVector& cVector): m_cVector(cVector)
				{
					m_iRangeStart = 0;
					m_iRangeLength = cVector.GetLength();
				}

				bool IsEmpty() const
				{
					return m_iRangeLength == 0;
				}

				size_t GetLength() const
				{
					return m_iRangeLength;
				}

				CType& Front()
				{
					return m_cVector[m_iRangeStart];
				}

				CType& PopFront()
				{
					m_iRangeStart++;
					m_iRangeLength--;
					return m_cVector[m_iRangeStart - 1];
				}

				CType& Back()
				{
					return m_cVector[m_iRangeStart + m_iRangeLength - 1];
				}

				CType& PopBack()
				{
					m_iRangeLength--;
					return m_cVector[m_iRangeStart + m_iRangeLength];
				}

				CType& At(size_t iIndex)
				{
					return m_cVector[m_iRangeStart + iIndex];
				}

				CType& operator[] (size_t iIndex)
				{
					return m_cVector[m_iRangeStart + iIndex];
				}
		};

		CVector()
		{
			m_pBuffer = NULL;
			m_iCapacity = 0;
			m_iLength = 0;
		}

		CVector(size_t iCapacity)
		{
			m_pBuffer = new CType[iCapacity];
			m_iCapacity = iCapacity;
			m_iLength = 0;
		}

		CVector(const CVector& cVector)
		{
			m_pBuffer = NULL;
			m_iCapacity = 0;
			m_iLength = 0;
			*this = cVector;
		}

		template<class CRange> CVector(CRange& cRange)
		{
			size_t iCapacity = cRange.GetLength();
			m_pBuffer = new CType[iCapacity];
			m_iCapacity = iCapacity;
			m_iLength = 0;
			while (!cRange.IsEmpty())
				PushBack(cRange.PopFront());
		}

		~CVector()
		{
			delete [] m_pBuffer;
		}

		CRange GetRange()
		{
			return CRange(*this);
		}

		void Allocate(size_t iNewCapacity)
		{
			if (m_iCapacity >= iNewCapacity)
				return;
			CType* pBuffer = new CType[iNewCapacity];
			Copy(m_pBuffer, m_pBuffer + m_iCapacity, pBuffer);
			delete [] m_pBuffer;
			m_pBuffer = pBuffer;
			m_iCapacity = iNewCapacity;
		}

		size_t GetLength() const
		{
			return m_iLength;
		}

		size_t GetCapacity() const
		{
			return m_iCapacity;
		}

		void Clear()
		{
			m_iLength = 0;
		}

		bool IsEmpty() const
		{
			return m_iLength == 0;
		}

		CType& operator[] (size_t iIndex)
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			return m_pBuffer[iIndex];
		}

		const CType& operator[] (size_t iIndex) const
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			return m_pBuffer[iIndex];
		}

		CType At(size_t iIndex) const
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			return m_pBuffer[iIndex];
		}

		CType& Front()
		{
			Assert(m_iLength > 0, "Empty vector");
			return m_pBuffer[0];
		}

		CType& Back()
		{
			Assert(m_iLength > 0, "Empty vector");
			return m_pBuffer[m_iLength - 1];
		}

		TMyType& operator= (const TMyType& cVector)
		{
			size_t iNewCapacity = cVector.m_iCapacity;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity);
			Copy(cVector.m_pBuffer, cVector.m_pBuffer + cVector.m_iLength, m_pBuffer);
			m_iLength = cVector.m_iLength;
			return *this;
		}

		void PushBack(const CType& cType)
		{
			if (m_iLength >= m_iCapacity)
				Allocate(m_iLength + m_iCapacity / 2 + 1);
			m_pBuffer[m_iLength] = cType;
			m_iLength++;
		}

		CType& PopBack()
		{
			Assert(m_iLength > 0, "Empty vector");
			m_iLength--;
			return m_pBuffer[m_iLength];
		}

		void Erase(size_t iIndex)
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			m_pBuffer[iIndex] = m_pBuffer[m_iLength - 1];
			m_iLength--;
		}

		void ErasePreserveOrder(size_t iIndex)
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			for (size_t i = iIndex; i < m_iLength - 1; ++i)
				m_pBuffer[i] = m_pBuffer[i + 1];
			m_iLength--;
		}
};

}

#endif /* COMMON_VECTOR_HPP */

/* EOF */
