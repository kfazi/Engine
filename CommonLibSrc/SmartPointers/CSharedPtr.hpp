#ifndef COMMON_CSharedPtr_HPP
#define COMMON_CSharedPtr_HPP

#include "../Internal.hpp"
#include "../Algorithms/Swap.hpp"
#include "CDeletePolicy.hpp"
#include "CDeleteArrayPolicy.hpp"

namespace Common
{

template <typename tType, typename tPolicy = CDeletePolicy>
class CSharedPtr
{
	template<typename tType2, typename tPolicy2> friend class CSharedPtr;

	private:
		tType* m_pData;
		unsigned int* m_iCounter;

	public:
		typedef tType tValue;
		typedef tType* tData;

		explicit CSharedPtr(tType* pData = NULL) : m_pData(pData), m_iCounter(pData ? new unsigned(1) : NULL)
		{
		}

		~CSharedPtr()
		{
			if (m_pData && --(*m_iCounter) == 0)
			{
				delete m_iCounter;
				tPolicy::template Delete<tType>(m_pData);
			}
		}
		
		CSharedPtr(const CSharedPtr& cSharedPointer) : m_pData(cSharedPointer.m_pData), m_iCounter(cSharedPointer.m_iCounter)
		{
			if (m_pData)
				(*m_iCounter)++;
		}

		CSharedPtr& operator= (const CSharedPtr& cSharedPointer)
		{
			Reset<tType>(cSharedPointer);
			return *this;
		}

		template <typename tType2, typename tPolicy2> explicit CSharedPtr(const CSharedPtr<tType2, tPolicy2>& cSharedPointer) : m_pData(cSharedPointer.m_pData), m_iCounter(cSharedPointer.m_iCounter)
		{
			if (m_pData)
				(*m_iCounter)++;
		}

		template <typename tType2, typename tPolicy2> CSharedPtr& operator= (const CSharedPtr<tType2, tPolicy2>& cSharedPointer)
		{
			Reset<tType2, tPolicy2>(cSharedPointer);
			return *this;
		}

		tType& operator* () const
		{
			Assert(m_pData != NULL, "Data is NULL");
			return *m_pData;
		}

		tType* operator-> () const
		{
			Assert(m_pData != NULL, "Data is NULL");
			return m_pData;
		}

		tType& operator[] (size_t iIndex) const
		{
			return m_pData[iIndex];
		}

		inline friend bool operator== (const CSharedPtr& cSharedPtr, const tType* pData)
		{
			return cSharedPtr.m_pData == pData;
		}
		
		inline friend bool operator== (const tType* pData, const CSharedPtr& cSharedPtr)
		{
			return cSharedPtr.m_pData == pData;
		}

		inline friend bool operator!= (const CSharedPtr& cSharedPtr, const tType* pData)
		{
			return cSharedPtr.m_pData != pData;
		}

		inline friend bool operator!= (const tType* pData, const CSharedPtr& cSharedPtr)
		{
			return cSharedPtr.m_pData != pData;
		}

		template <typename tType2, typename tPolicy2> bool operator== (const CSharedPtr<tType2, tPolicy2>& cSharedPtr) const
		{
			return cSharedPtr.m_pData == m_pData;
		}

		template <typename tType2, typename tPolicy2> bool operator!= (const CSharedPtr<tType2, tPolicy2>& cSharedPtr) const
		{
			return cSharedPtr.m_pData != m_pData;
		}

		tType* Get() const
		{
			return m_pData;
		}

		void Swap(CSharedPtr<tType, tPolicy>& cSharedPtr)
		{
			Common::Swap(cSharedPtr.m_pData, m_pData);
			Common::Swap(cSharedPtr.m_iCounter, m_iCounter);
		}

		void Reset(tType* pData = NULL)
		{
			if (pData == m_pData)
				return;
			CSharedPtr<tType, tPolicy>(pData).Swap(*this);
		}

		template <typename tType2, typename tPolicy2> void Reset(const CSharedPtr<tType2, tPolicy2>& cSharedPtr)
		{
			CSharedPtr<tType2, tPolicy2>(cSharedPtr).Swap(*this);
		}

		bool Unique() const
		{
			return m_iCounter == NULL || *m_iCounter == 1;
		}

		bool IsNull()
		{
			return m_pData == NULL;
		}
};

}

#endif /* COMMON_CSharedPtr_HPP */

/* EOF */
