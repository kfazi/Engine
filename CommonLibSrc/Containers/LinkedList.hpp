#ifndef COMMON_LINKED_LIST_HPP
#define COMMON_LINKED_LIST_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"

namespace Common
{

template<class Type> class LinkedList
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

		template<typename Type, typename NonConstType, typename ConstType> class IteratorBase
		{
			friend class IteratorBase<NonConstType, NonConstType, ConstType>;
			friend class IteratorBase<ConstType, NonConstType, ConstType>;

			public:
				explicit IteratorBase(Node* node) : mNode(node)
				{
				}

				IteratorBase() : mNode(NULL)
				{
				}

				IteratorBase(const IteratorBase<NonConstType, NonConstType, ConstType>& iterator) : mNode(iterator.mNode)
				{
				}

				IteratorBase& operator++ ()
				{
					mNode = mNode->next;
					return *this;
				}

				IteratorBase& operator++ (int)
				{
					mNode = mNode->next;
					return *this;
				}

				IteratorBase& operator-- ()
				{
					mNode = mNode->previous;
					return *this;
				}

				IteratorBase& operator-- (int)
				{
					mNode = mNode->previous;
					return *this;
				}

				bool operator== (const IteratorBase<ConstType, NonConstType, ConstType>& iterator) const
				{
					return mNode == iterator.mNode;
				}

				bool operator!= (const IteratorBase<ConstType, NonConstType, ConstType>& iterator) const
				{
					return mNode != iterator.mNode;
				}

				Type& operator* () const
				{
					return mNode->data;
				}

			private:
				Node* mNode;
		};

	public:
		typedef LinkedList<Type> MyType;
		typedef const Type& ConstReference;
		typedef Type& Reference;
		typedef const Type* ConstPointer;
		typedef Type* Pointer;
		typedef IteratorBase<const Type, Type, const Type> ConstIterator;
		typedef IteratorBase<Type, Type, const Type> Iterator;

		LinkedList()
		{
			mRoot = NULL;
		}

		LinkedList(const LinkedList& list)
		{
			mRoot = NULL;
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
				if (node == NULL)
				{
					mRoot = new Node(*i);
					node = mRoot;
				}
				else
				{
					node->next = new Node(*i);
					node = node->next;
				}
			}
			return *this;
		}

		Iterator Begin()
		{
			return Iterator(mRoot);
		}

		ConstIterator Begin() const
		{
			return ConstIterator(mRoot);
		}

		Iterator End()
		{
			return Iterator();
		}

		ConstIterator End() const
		{
			return ConstIterator();
		}

		void Clear()
		{
			while (!IsEmpty())
				PopFront();
		}

		bool IsEmpty() const
		{
			return mRoot == NULL;
		}

		Type& Front()
		{
			Assert(!IsEmpty(), "Empty list");
			return mRoot->data;
		}

		void PushFront(const Type& data)
		{
			if (mRoot == NULL)
				mRoot = new Node(data);
			else
			{
				Node* new_root = new Node(data);
				new_root->next = mRoot;
				mRoot = new_root;
			}
		}

		Type PopFront()
		{
			Assert(!IsEmpty(), "Empty list");
			Node* node = mRoot;
			Type result = mRoot->data;
			mRoot = mRoot->next;
			delete node;
			return result;
		}

	private:
		Node* mRoot;
};

}

#endif /* COMMON_LINKED_LIST_HPP */

/* EOF */
