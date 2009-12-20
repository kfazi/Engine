#ifndef COMMON_SINGLY_LINKED_LIST_HPP
#define COMMON_SINGLY_LINKED_LIST_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"

namespace Common
{

template<class CType> class CSinglyLinkedList
{
	private:
		typedef CSinglyLinkedList<CType> TMyType;
		struct SNode
		{
			CType cData;
			SNode* pNext;

			SNode(const CType& cData): cData(cData)
			{
				pNext = NULL;
			}
		};
		SNode* m_pRoot;
		SNode* m_pTail;
		size_t m_iLength;

	public:
		class CRange
		{
			friend class CSinglyLinkedList;

			private:
				CSinglyLinkedList& m_cList;

				CRange(CSinglyLinkedList& cList, size_t iRangeStart, size_t iRangeLength): m_cList(cList)
				{
				}

			public:
				CType& PopFront()
				{
					return m_cList[0];
				}

				bool IsEmpty() const
				{
					return true;
				}
		};

		CSinglyLinkedList()
		{
			m_pRoot = NULL;
			m_pTail = NULL;
			m_iLength = 0;
		}

		CSinglyLinkedList(const CSinglyLinkedList& cList)
		{
			m_pRoot = NULL;
			m_pTail = NULL;
			m_iLength = 0;
			*this = cList;
		}

		template<class CRange2> CSinglyLinkedList(CRange2& cRange)
		{
			m_pRoot = NULL;
			m_pTail = NULL;
			m_iLength = 0;
			while (!cRange.IsEmpty())
				PushBack(cRange.PopFront());
		}

		~CSinglyLinkedList()
		{
			Clear();
		}

		CRange GetRange()
		{
			return CRange(*this, 0, m_iLength);
		}

		CRange GetRange(size_t iStart, size_t iLength)
		{
			return CRange(*this, iStart, iLength);
		}

		CRange GetAppendRange()
		{
			return CRange(*this, m_iLength, 0);
		}

		size_t GetLength() const
		{
			return m_iLength;
		}

		void Clear()
		{
			while (!IsEmpty())
				PopFront();
		}

		bool IsEmpty() const
		{
			return m_iLength == 0;
		}

		CType& Front()
		{
			Assert(!IsEmpty(), "Empty list");
			return m_pRoot->cData;
		}

		template<class CRange2> TMyType& operator= (CRange2& cRange)
		{
			Assert(false, "NO KURWA JAK :?");
			Clear();
			while (!cRange.IsEmpty())
				PushBack(cRange.PopFront());
			return *this;
		}

//		TMyType& operator= (const TMyType& cList)
//		{
//			Clear();
//			CRange cRange = cList.GetRange(0, m_iLength);
//			while (!cRange.IsEmpty())
//				PushBack(cRange.PopFront());
//			return *this;
//		}

		CType& operator[] (size_t iIndex)
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			SNode* pNode = m_pRoot;
			for (int i = 0; i < iIndex; ++i)
				pNode = pNode->pNext;
			return pNode->cData;
		}

		const CType& operator[] (size_t iIndex) const
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			SNode* pNode = m_pRoot;
			for (int i = 0; i < iIndex; ++i)
				pNode = pNode->pNext;
			return pNode->cData;
		}

		CType& At(size_t iIndex) const
		{
			Assert(m_iLength > iIndex, "Index out of bounds");
			SNode* pNode = m_pRoot;
			for (int i = 0; i < iIndex; ++i)
				pNode = pNode->pNext;
			return pNode->cData;
		}

		void PushBack(const CType& cType)
		{
			if (m_pTail == NULL)
			{
				m_pTail = new SNode(cType);
				m_pRoot = m_pTail;
			}
			else
			{
				m_pTail->pNext = new SNode(cType);
				m_pTail = m_pTail->pNext;
			}
			m_iLength++;
		}

		void PushFront(const CType& cType)
		{
			if (m_pRoot == NULL)
			{
				m_pRoot = new SNode(cType);
				m_pTail = m_pRoot;
			}
			else
			{
				SNode* pNewRoot = new SNode(cType);
				pNewRoot->pNext = m_pRoot;
				m_pRoot = pNewRoot;
			}
			m_iLength++;
		}

		CType PopFront()
		{
			Assert(!IsEmpty(), "Empty list");
			SNode* pNode = m_pRoot;
			CType cResult = m_pRoot->cData;
			if (m_pRoot == m_pTail)
				m_pTail = m_pRoot->pNext;
			m_pRoot = m_pRoot->pNext;
			m_iLength--;
			delete pNode;
			return cResult;
		}

		CType PopBack()
		{
			Assert(!IsEmpty(), "Empty list");
			m_iLength--;
			switch (m_iLength)
			{
				case 0:
					{
						CType cResult = m_pRoot->cData;
						delete m_pRoot;
						m_pRoot = NULL;
						m_pTail = NULL;
						return cResult;
					}
				case 1:
					{
						CType cResult = m_pRoot->pNext->cData;
						delete m_pRoot->pNext;
						m_pRoot->pNext = NULL;
						m_pTail = m_pRoot;
						return cResult;
					}
				default:
					{
						SNode* pNode = m_pRoot;
						for (int i = 0; i < m_iLength - 1; ++i)
							pNode = pNode->pNext;
						CType cResult = pNode->pNext->cData;
						delete pNode->pNext;
						pNode->pNext = NULL;
						m_pTail = pNode;
						return cResult;
					}
			}
		}
};

}

#endif /* COMMON_SINGLY_LINKED_LIST_HPP */

/* EOF */
