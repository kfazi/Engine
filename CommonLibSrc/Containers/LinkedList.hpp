#ifndef COMMON_LINKED_LIST_HPP
#define COMMON_LINKED_LIST_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"
#include "../Iterators/IteratorTags.hpp"
#include "../Iterators/ReverseIteratorBase.hpp"

namespace Common
{

template<class Type, class Allocator = DefaultAllocator<Type> > class LinkedList
{
	private:
		struct Node
		{
			Node(const Type& data): data(data), previous(NULL), next(NULL)
			{
			}

			Type data;
			Node* previous;
			Node* next;
		};

	public:
		template<typename Type, typename NonConstType, typename ConstType> class IteratorBase :
			public BidirectionalIteratorTag<Type, Type*, Type&>
		{
			friend class IteratorBase<NonConstType, NonConstType, ConstType>;
			friend class IteratorBase<ConstType, NonConstType, ConstType>;
			friend class LinkedList;

			public:
				typedef IteratorBase<NonConstType, NonConstType, ConstType> NonConstIteratorType;
				typedef IteratorBase<ConstType, NonConstType, ConstType> ConstIteratorType;
				typedef IteratorBase<Type, NonConstType, ConstType> MyType;

				explicit IteratorBase(Node* node, const LinkedList* list) : mNode(node), mList(list)
				{
				}

				IteratorBase() : mNode(NULL), mList(NULL)
				{
				}

				IteratorBase(const NonConstIteratorType& iterator) : mNode(iterator.mNode),
					mList(iterator.mList)
				{
				}

				MyType& operator++ ()
				{
					Assert(mNode != NULL, "Iterator out of range");
					mNode = mNode->next;
					return *this;
				}

				MyType& operator++ (int)
				{
					Assert(mNode != NULL, "Iterator out of range");
					mNode = mNode->next;
					return *this;
				}

				MyType& operator-- ()
				{
					if (mNode != NULL)
					{
						Assert(mNode->previous != NULL, "Iterator out of range");
						mNode = mNode->previous;
					}
					else
					{
						Assert(mList->mTail != NULL, "Iterator out of range");
						mNode = mList->mTail;
					}
					return *this;
				}

				MyType& operator-- (int)
				{
					if (mNode != NULL)
					{
						Assert(mNode->previous != NULL, "Iterator out of range");
						mNode = mNode->previous;
					}
					else
					{
						Assert(mList->mTail != NULL, "Iterator out of range");
						mNode = mList->mTail;
					}
					return *this;
				}

				bool operator== (const ConstIteratorType& iterator) const
				{
					return mNode == iterator.mNode;
				}

				bool operator!= (const ConstIteratorType& iterator) const
				{
					return mNode != iterator.mNode;
				}

				Type& operator* () const
				{
					return mNode->data;
				}

				/*!
				 * Returns pointer to current element.
				 *
				 * \return Pointer to current element.
				 */
				Pointer operator-> () const
				{
					return &(operator*());
				}

			private:
				Node* mNode;
				const LinkedList* mList;
		};

		typedef typename Allocator::Rebind<Node>::Other NodeAllocator;
		typedef LinkedList<Type> MyType;
		typedef const Type& ConstReference;
		typedef Type& Reference;
		typedef const Type* ConstPointer;
		typedef Type* Pointer;
		typedef IteratorBase<Type, Type, const Type> Iterator;
		typedef IteratorBase<const Type, Type, const Type> ConstIterator;
		typedef ReverseIteratorBase<Iterator> ReverseIterator; /*!< Reverse iterator. */
		typedef ReverseIteratorBase<ConstIterator>
			ConstReverseIterator; /*!< Constant reverse iterator. */

		LinkedList()
		{
			mHead = NULL;
			mTail = NULL;
		}

		LinkedList(const LinkedList& list)
		{
			mHead = NULL;
			mTail = NULL;
			*this = list;
		}

		~LinkedList()
		{
			Clear();
		}

		MyType& operator= (const MyType& list)
		{
			Clear();
			Node* node = NULL;
			for (ConstIterator i = list.Begin(); i != list.End(); ++i)
			{
				if (node != NULL)
				{
					node->next = new Node(*i);
					node = node->next;
				}
				else
				{
					mHead = new Node(*i);
					node = mHead;
				}
				mTail = node;
			}
			return *this;
		}

		Iterator Begin()
		{
			return Iterator(mHead, this);
		}

		ConstIterator Begin() const
		{
			return ConstIterator(mHead, this);
		}

		Iterator End()
		{
			return Iterator(NULL, this);
		}

		ConstIterator End() const
		{
			return ConstIterator(NULL, this);
		}

		/*!
		 * Returns iterator pointing to the last element.
		 *
		 * \return Iterator pointing to the last element.
		 */
		ReverseIterator ReverseBegin()
		{
			return ReverseIterator(End());
		}

		/*!
		 * Returns iterator pointing to the last element.
		 *
		 * \return Iterator pointing to the last element.
		 */
		ConstReverseIterator ReverseBegin() const
		{
			return ConstReverseIterator(End());
		}

		/*!
		 * Returns iterator pointing to one before first element.
		 *
		 * \return Iterator pointing to one before first element.
		 */
		ReverseIterator ReverseEnd()
		{
			return ReverseIterator(Begin());
		}

		/*!
		 * Returns iterator pointing to one before first element.
		 *
		 * \return Iterator pointing to one before first element.
		 */
		ConstReverseIterator ReverseEnd() const
		{
			return ConstReverseIterator(Begin());
		}

		void Clear()
		{
			while (!IsEmpty())
				PopFront();
		}

		bool IsEmpty() const
		{
			return mHead == NULL;
		}

		Type& Front()
		{
			Assert(!IsEmpty(), "Empty list");
			return mHead->data;
		}

		Type& Back()
		{
			Assert(!IsEmpty(), "Empty list");
			return mTail->data;
		}

		Iterator PushFront(const Type& data)
		{
			if (mHead != NULL)
			{
				Node* new_root = new Node(data);
				new_root->next = mHead;
				mHead->previous = new_root;
				mHead = new_root;
			}
			else
			{
				mHead = new Node(data);
				mTail = mHead;
			}
			return Iterator(mHead, this);
		}

		Iterator PushBack(const Type& data)
		{
			if (mTail != NULL)
			{
				Node* new_tail = new Node(data);
				new_tail->previous = mTail;
				mTail->next = new_tail;
				mTail = new_tail;
			}
			else
			{
				mTail = new Node(data);
				mHead = mTail;
			}
			return Iterator(mTail, this);
		}

		Type PopFront()
		{
			Assert(!IsEmpty(), "Empty list");
			Node* node = mHead;
			Type result = mHead->data;
			mHead = mHead->next;
			if (mHead)
				mHead->previous = NULL;
			else
				mTail = NULL;
			delete node;
			return result;
		}

		Type PopBack()
		{
			Assert(!IsEmpty(), "Empty list");
			Node* node = mTail;
			Type result = mTail->data;
			mTail = mTail->previous;
			if (mTail)
				mTail->next = NULL;
			else
				mHead = NULL;
			delete node;
			return result;
		}

		Iterator Erase(Iterator iterator)
		{
			Node* node = iterator.mNode;
			Node* previous_node = node->previous;
			Node* next_node = node->next;
			if (previous_node)
				previous_node->next = next_node;
			if (next_node)
				next_node->previous = previous_node;
			if (node == mHead)
				mHead = node->next;
			if (node == mTail)
				mTail = node->previous;
			delete node;
			return Iterator(next_node, this);
		}

	private:
		Node* mHead;
		Node* mTail;
};

}

#endif /* COMMON_LINKED_LIST_HPP */

/* EOF */
