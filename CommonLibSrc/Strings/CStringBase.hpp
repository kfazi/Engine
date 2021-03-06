#ifndef COMMON_STRING_BASE_HPP
#define COMMON_STRING_BASE_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"
#include "CStringStatic.hpp"

namespace Common
{

template<typename TCharType> class CStringIterator;

template<typename TCharType> class CStringBase: private CStringStatic
{
	private:
		typedef CStringBase<TCharType> TMyType;
		unsigned int m_iLength;
		unsigned int m_iCapacity;
		TCharType *m_pBuffer;

	public:
		typedef CStringIterator<TCharType> TIterator;
		typedef CStringIterator<const TCharType> TConstIterator;

		CStringBase()
		{
			m_pBuffer = 0;
			m_iCapacity = 0;
			m_iLength = 0;
		}

		CStringBase(unsigned int iCapacity)
		{
			m_iCapacity = iCapacity;
			m_pBuffer = new TCharType[m_iCapacity];
			m_pBuffer[0] = 0;
			m_iLength = 0;
		}

		CStringBase(const TMyType& cStringBase)
		{
			m_iCapacity = cStringBase.m_iCapacity;
			m_iLength = cStringBase.GetLength();
			m_pBuffer = new TCharType[m_iCapacity];
			Copy(cStringBase.m_pBuffer, cStringBase.m_pBuffer + GetLength() + 1, m_pBuffer);
		}

		CStringBase(const TCharType* pString)
		{
			unsigned int iLength = 0;
			while (pString[iLength])
				iLength++;
			m_iCapacity = iLength + 1 + GetBaseCapacity();
			m_iLength = iLength;
			m_pBuffer = new TCharType[m_iCapacity];
			Copy(pString, pString + GetLength() + 1, m_pBuffer);
		}

		CStringBase(const TCharType* pString, unsigned int iLength)
		{
			m_iCapacity = iLength + 1 + GetBaseCapacity();
			m_iLength = iLength;
			m_pBuffer = new TCharType[m_iCapacity];
			Copy(pString, pString + GetLength() + 1, m_pBuffer);
		}

		~CStringBase()
		{
			delete [] m_pBuffer;
		}

		void Allocate(unsigned int iNewCapacity)
		{
			if (m_iCapacity >= iNewCapacity)
				return;
			iNewCapacity += GetBaseCapacity();
			TCharType* pBuffer = new TCharType[iNewCapacity];
			Copy(m_pBuffer, m_pBuffer + GetLength() + 1, pBuffer);
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
			m_pBuffer[0] = 0;
			m_iLength = 0;
		}

		bool IsEmpty() const
		{
			return m_iLength == 0;
		}

		TCharType& operator[] (unsigned int iIndex)
		{
			return m_pBuffer[iIndex];
		}

		const TCharType& operator[] (unsigned int iIndex) const
		{
			return m_pBuffer[iIndex];
		}

		TCharType At(unsigned int iIndex) const
		{
			return m_pBuffer[iIndex];
		}

		TMyType& operator+= (const TMyType& cStringBase)
		{
			unsigned int iNewCapacity = GetLength() + cStringBase.GetLength() + 1;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity + GetBaseCapacity());
			Copy(cStringBase.m_pBuffer, cStringBase.m_pBuffer + cStringBase.GetLength() + 1, m_pBuffer + GetLength());
			m_iLength = GetLength() + cStringBase.GetLength();
			return *this;
		}

		TMyType& operator+= (const TCharType* pString)
		{
			unsigned int iLength = 0;
			while (pString[iLength])
				iLength++;
			unsigned int iNewCapacity = GetLength() + iLength + 1;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity + GetBaseCapacity());
			Copy(pString, pString + iLength + 1, m_pBuffer + GetLength());
			m_iLength = GetNewLength();
			return *this;
		}

		TMyType& operator+= (TCharType tChar)
		{
			unsigned int iNewCapacity = GetLength() + 2;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity + GetBaseCapacity());
			m_pBuffer[GetLength()] = tChar;
			m_pBuffer[GetLength() + 1] = 0;
			m_iLength = GetNewLength();
			return *this;
		}

		TMyType& operator= (const TMyType& cStringBase)
		{
			unsigned int iNewCapacity = cStringBase.m_iCapacity;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity);
			Copy(cStringBase.m_pBuffer, cStringBase.m_pBuffer + cStringBase.GetLength() + 1, m_pBuffer);
			m_iLength = cStringBase.GetLength();
			return *this;
		}

		TMyType& operator= (const TCharType* pString)
		{
			unsigned int iLength = 0;
			while (pString[iLength])
				iLength++;
			unsigned int iNewCapacity = iLength + 1;
			if (iNewCapacity > m_iCapacity)
				Allocate(iNewCapacity);
			Copy(pString, pString + iLength + 1, m_pBuffer);
			m_iLength = iLength;
			return *this;
		}

		TMyType& operator= (TCharType tChar)
		{
			m_pBuffer[0] = tChar;
			m_pBuffer[1] = 0;
			m_iLength = 1;
			return *this;
		}

		const TCharType *GetRaw() const
		{
			return m_pBuffer;
		}

		void ToUpper()
		{
			/* TODO: UnicodeData.txt */
		}

		void ToLower()
		{
			/* TODO: UnicodeData.txt (http://www.unicode.org/Public/5.2.0/)*/
		}
};

}

#endif /* COMMON_STRING_BASE_HPP */

/* EOF */
