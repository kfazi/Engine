#ifndef COMMON_VECTOR_HPP
#define COMMON_VECTOR_HPP

namespace Common
{

template<class CType> class CVector
{
	private:
		typedef CVector<CType> TMyType;
		unsigned int m_iLength;
		unsigned int m_iCapacity;
		CType* m_pBuffer;

	public:
		CVector()
		{
			m_pBuffer = 0;
			m_iCapacity = 0;
			m_iLength = 0;
		}

		CVector(unsigned int iCapacity)
		{
			m_iCapacity = iCapacity;
			m_pBuffer = new CType[m_iCapacity];
			m_iLength = 0;
		}

		~CVector()
		{
			delete [] m_pBuffer;
		}

		void Allocate(unsigned int iNewCapacity)
		{
			if (m_iCapacity >= iNewCapacity)
				return;
			CType* pBuffer = new CType[iNewCapacity];
			Copy(m_pBuffer, m_pBuffer + m_iLength, pBuffer);
			delete [] m_pBuffer;
			m_pBuffer = pBuffer;
			m_iCapacity = iNewCapacity;
		}

		unsigned int GetLength() const
		{
			return m_iLength;
		}

		unsigned int GetCapacity() const
		{
			return m_iCapacity;
		}

		void Clear()
		{
			for (int i = 0; i < m_iLength; ++i)
				m_pBuffer[i].~CType();
			m_iLength = 0;
		}

		bool IsEmpty() const
		{
			return m_iLength == 0;
		}

		CType& operator [] (unsigned int iIndex)
		{
			return m_pBuffer[iIndex];
		}

		const CType& operator [] (unsigned int iIndex) const
		{
			return m_pBuffer[iIndex];
		}

		CType At(unsigned int iIndex) const
		{
			return m_pBuffer[iIndex];
		}

		CType& Front()
		{
			return m_pBuffer[0];
		}

		CType& Back()
		{
			return m_pBuffer[GetLength() - 1];
		}

		TMyType& operator = (const TMyType& cVector)
		{
			unsigned int iNewCapacity = cVector.m_iCapacity;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity);
			Copy(cVector.m_pBuffer, cVector.m_pBuffer + cVector.GetLength(), m_pBuffer);
			m_iLength = cVector.GetLength();
			return *this;
		}

		void PushBack(const CType& cType)
		{
			if (m_iLength >= m_iCapacity)
				Allocate(m_iLength + 1024);
			m_pBuffer[m_iLength] = cType;
			m_iLength++;
		}

		void PopBack()
		{
			m_iLength--;
			m_pBuffer[m_iLength].~CType();
		}

		void Erase(unsigned int iIndex)
		{
			m_pBuffer[iIndex].~CType();
			m_pBuffer[iIndex] = m_pBuffer[GetLength() - 1];
			m_iLength--;
		}

		void ErasePreserveOrder(unsigned int iIndex)
		{
			m_pBuffer[iIndex].~CType();
			for (int i = iIndex; iIndex < GetLength() - 1; ++i)
				m_pBuffer[i] = m_pBuffer[i + 1];
			m_iLength--;
		}

		void Insert(unsigned int iIndex, const CType& cType)
		{
			if (m_iLength >= m_iCapacity)
				Allocate(m_iLength + 1024);
			for (int i = iIndex; i <= GetLength(); ++i)
				m_pBuffer[i + 1] = m_pBuffer[i];
			m_pBuffer[iIndex] = cType;
			m_iLength++;
		}
};

}

#endif /* COMMON_VECTOR_HPP */

/* EOF */
