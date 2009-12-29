/**
 * A singly linked list class.
 *
 * #include "SinglyLinkedList.hpp"
 * -lcommonlib
 *
 * This is implementation of a singly linked list container.
 */

#ifndef COMMON_SINGLY_LINKED_LIST_HPP
#define COMMON_SINGLY_LINKED_LIST_HPP

#include "../Internal.hpp"
#include "../Iterators/IteratorTags.hpp"

namespace Common
{

template<class Type, class Allocator = DefaultAllocator<Type> > class SinglyLinkedList
{
	private:
		struct Node
		{
			Node(const Type& data) : data(data), next(NULL)
			{
			}

			Type data;
			Node* next;
		};

		template<typename Type, typename NonConstType, typename ConstType> class IteratorBase : public ForwardIteratorTag
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
		typedef SinglyLinkedList<Type, Allocator> MyType;
		typedef const Type& ConstReference;
		typedef Type& Reference;
		typedef const Type* ConstPointer;
		typedef Type* Pointer;
		typedef IteratorBase<const Type, Type, const Type> ConstIterator;
		typedef IteratorBase<Type, Type, const Type> Iterator;

		SinglyLinkedList()
		{
			mRoot = NULL;
		}

		SinglyLinkedList(const SinglyLinkedList& list)
		{
			mRoot = NULL;
			*this = list;
		}

		~SinglyLinkedList()
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
					node->next = mNodeAllocator.Allocate(1);
					Assert(node->next != NULL, "Allocation failed");
					mNodeAllocator.Construct(node->next, *i);
					node = node->next;
				}
				else
				{
					mRoot = mNodeAllocator.Allocate(1);
					Assert(mRoot != NULL, "Allocation failed");
					mNodeAllocator.Construct(mRoot, *i);
					node = mRoot;
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
			{
				Node* node = mRoot;
				mRoot = mRoot->next;
				mNodeAllocator.Destroy(node);
				mNodeAllocator.Deallocate(node);
			}
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
			if (mRoot != NULL)
			{
				Node* new_root = mNodeAllocator.Allocate(1);
				Assert(new_root != NULL, "Allocation failed");
				mNodeAllocator.Construct(new_root, Node(data));
				new_root->next = mRoot;
				mRoot = new_root;
			}
			else
			{
				mRoot = mNodeAllocator.Allocate(1);
				Assert(mRoot != NULL, "Allocation failed");
				mNodeAllocator.Construct(mRoot, Node(data));
			}
		}

		Type PopFront()
		{
			Assert(!IsEmpty(), "Empty list");
			Node* node = mRoot;
			Type result = mRoot->data;
			mRoot = mRoot->next;
			mNodeAllocator.Destroy(node);
			mNodeAllocator.Deallocate(node);
			return result;
		}

	private:
		Node* mRoot;
		typename Allocator::Rebind<Node>::Other mNodeAllocator;
};

}

#endif /* COMMON_SINGLY_LINKED_LIST_HPP */

/* EOF */
