#ifndef COMMON_VECTOR_HPP
#define COMMON_VECTOR_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"
#include "../SmartPointers/CSharedPtr.hpp"

namespace Common
{

template<class CType> class CVector
{
	private:
		struct SData
		{
			size_t iCapacity;
			CType* pBuffer;
		};

		typedef CVector<CType> TMyType;
		CSharedPtr<SData> m_pData;
		size_t m_iRangeStart;
		size_t m_iRangeLength;

	public:
		CVector(): m_pData(new SData())
		{
			m_pData->pBuffer = 0;
			m_pData->iCapacity = 0;
			m_iRangeStart = 0;
			m_iRangeLength = 0;
		}

		CVector(size_t iCapacity): m_pData(new SData())
		{
			m_pData->pBuffer = new CType[iCapacity];
			m_pData->iCapacity = iCapacity;
			m_iRangeStart = 0;
			m_iRangeLength = 0;
		}

		~CVector()
		{
			if (m_pData.Unique())
				delete [] m_pData->pBuffer;
		}

		void Allocate(size_t iNewCapacity)
		{
			if (m_pData->iCapacity >= iNewCapacity)
				return;
			CType* pBuffer = new CType[iNewCapacity];
			Copy(m_pData->pBuffer, m_pData->pBuffer + m_pData->iCapacity, pBuffer);
			delete [] m_pData->pBuffer;
			m_pData->pBuffer = pBuffer;
			m_pData->iCapacity = iNewCapacity;
		}

		size_t GetLength() const
		{
			return m_iRangeLength;
		}

		size_t GetCapacity() const
		{
			Assert(m_pData->iCapacity >= m_iRangeStart, "Negative capacity");
			return m_pData->iCapacity - m_iRangeStart;
		}

		void Clear()
		{
			m_iRangeLength = 0;
		}

		bool IsEmpty() const
		{
			return m_iRangeLength == 0;
		}

		CType& operator[] (size_t iIndex)
		{
			Assert(m_iRangeLength > iIndex, "Index out of bounds");
			return m_pData->pBuffer[m_iRangeStart + iIndex];
		}

		const CType& operator[] (size_t iIndex) const
		{
			Assert(m_iRangeLength > iIndex, "Index out of bounds");
			return m_pData->pBuffer[m_iRangeStart + iIndex];
		}

		CType At(size_t iIndex) const
		{
			Assert(m_iRangeLength > iIndex, "Index out of bounds");
			return m_pData->pBuffer[m_iRangeStart + iIndex];
		}

		CType& Front()
		{
			Assert(m_iRangeLength > 0, "Empty range");
			return m_pData->pBuffer[m_iRangeStart];
		}

		CType& Back()
		{
			Assert(m_iRangeLength > 0, "Empty range");
			return m_pData->pBuffer[m_iRangeLength - 1];
		}

		TMyType& operator= (const TMyType& cVector)
		{
			size_t iNewCapacity = cVector.m_pData->iCapacity;
			if (iNewCapacity > m_pData->iCapacity)
				Allocate(iNewCapacity);
			Copy(cVector.m_pData->pBuffer, cVector.m_pData->pBuffer + cVector.m_iRangeLength, m_pData->pBuffer);
			m_iRangeStart = cVector.m_iRangeStart;
			m_iRangeLength = cVector.m_iRangeLength;
			return *this;
		}

		void Put(const CType& cType)
		{
			if (m_iRangeStart + m_iRangeLength >= m_pData->iCapacity)
				Allocate(m_iRangeStart + m_iRangeLength + 1024);
			m_pData->pBuffer[m_iRangeStart + m_iRangeLength] = cType;
			m_iRangeLength++;
		}

		void PopBack()
		{
			Assert(m_iRangeLength > 0, "Empty range");
			m_iRangeLength--;
		}

		void Erase(size_t iIndex)
		{
			Assert(m_iRangeLength > iIndex, "Index out of bounds");
			m_pData->pBuffer[m_iRangeStart + iIndex] = m_pData->pBuffer[m_iRangeStart + m_iRangeLength - 1];
			m_iRangeLength--;
		}

		void ErasePreserveOrder(size_t iIndex)
		{
			Assert(m_iRangeLength > iIndex, "Index out of bounds");
			for (size_t i = m_iRangeStart + iIndex; i < m_iRangeStart + m_iRangeLength - 1; ++i)
				m_pData->pBuffer[i] = m_pData->pBuffer[i + 1];
			m_iRangeLength--;
		}
};

}

#endif /* COMMON_VECTOR_HPP */

/* EOF */
