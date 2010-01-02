/**
 * A vector class.
 *
 * #include "Vector.hpp"
 * -lcommonlib
 *
 * This is equivalent of std::vector.
 * Two main differences are:
 * - Erase() doesn't preserve order, if you want to preserve order use ErasePreserveOrder().
 * - For most algorithms you should use ranges (through GetRange()) instead of iterators.
 */

#ifndef COMMON_VECTOR_HPP
#define COMMON_VECTOR_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"
#include "../Iterators/IteratorTags.hpp"
#include "../Iterators/ReverseIterator.hpp"

namespace Common
{

template<class Type, class Allocator = DefaultAllocator<Type> > class Vector
{
	public:
		/* Typedefs. */
		typedef Vector<Type> MyType;
		typedef const Type& ConstReference;
		typedef Type& Reference;
		typedef const Type* ConstPointer;
		typedef Type* Pointer;

		template<typename Type, typename NonConstType, typename ConstType> class IteratorBase : public RandomAccessIteratorTag<Type, Type*, Type&>
		{
			friend class IteratorBase<NonConstType, NonConstType, ConstType>;
			friend class IteratorBase<ConstType, NonConstType, ConstType>;

			public:
				typedef Type& Reference;

				explicit IteratorBase(Type* address) : mAddress(address)
				{
				}

				IteratorBase() : mAddress(NULL)
				{
				}

				IteratorBase(const IteratorBase<NonConstType, NonConstType, ConstType>& iterator) : mAddress(iterator.mAddress)
				{
				}

				IteratorBase& operator++ ()
				{
					mAddress++;
					return *this;
				}

				IteratorBase& operator++ (int)
				{
					IteratorBase<Type, NonConstType, ConstType> iterator = *this;
					mAddress++;
					return iterator;
				}

				IteratorBase& operator-- ()
				{
					mAddress--;
					return *this;
				}

				IteratorBase& operator-- (int)
				{
					IteratorBase<Type, NonConstType, ConstType> iterator = *this;
					mAddress--;
					return iterator;
				}

				bool operator== (const IteratorBase<ConstType, NonConstType, ConstType>& iterator) const
				{
					return mAddress == iterator.mAddress;
				}

				bool operator!= (const IteratorBase<ConstType, NonConstType, ConstType>& iterator) const
				{
					return mAddress != iterator.mAddress;
				}

				Reference operator* () const
				{
					return *mAddress;
				}

				Pointer operator-> () const
				{
					return &(operator*());
				}

			private:
				Type* mAddress;
		};

		typedef IteratorBase<const Type, Type, const Type> ConstIterator;
		typedef IteratorBase<Type, Type, const Type> Iterator;
		typedef Common::ReverseIterator<Iterator> ReverseIterator;
		typedef Common::ReverseIterator<ConstIterator> ConstReverseIterator;

		Vector(): mBegin(NULL), mEnd(NULL), mCapacity(0)
		{
		}

		Vector(size_t capacity): mBegin(mAllocator.Allocate(capacity)), mCapacity(capacity)
		{
			Assert(mBegin != NULL, "Allocation failed");
			mEnd = mBegin;
		}

		Vector(const Vector& vector): mBegin(NULL), mEnd(NULL), mCapacity(0)
		{
			*this = vector;
		}

		~Vector()
		{
			Clear();
			mAllocator.Deallocate(mBegin);
		}

		MyType& operator= (const MyType& vector)
		{
			size_t iNewCapacity = vector.mCapacity;
			if (iNewCapacity > mCapacity)
				Allocate(iNewCapacity);
			Copy(vector.mBegin, vector.mEnd, mBegin);
			mEnd = mBegin + (vector.mEnd - vector.mBegin);
			return *this;
		}

		Reference operator[] (size_t index)
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			return mBegin[index];
		}

		ConstReference operator[] (size_t index) const
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			return mBegin[index];
		}

		Iterator Begin()
		{
			return Iterator(mBegin);
		}

		ConstIterator Begin() const
		{
			return ConstIterator(mBegin);
		}

		Iterator End()
		{
			return Iterator(mEnd);
		}

		ConstIterator End() const
		{
			return ConstIterator(mEnd);
		}

		ReverseIterator ReverseBegin()
		{
			return ReverseIterator(Iterator(mEnd));
		}

		ConstReverseIterator ReverseBegin() const
		{
			return ConstReverseIterator(ConstIterator(mEnd));
		}

		ReverseIterator ReverseEnd()
		{
			return ReverseIterator(Iterator(mBegin));
		}

		ConstReverseIterator ReverseEnd() const
		{
			return ConstReverseIterator(ConstIterator(mBegin));
		}

		void Allocate(size_t capacity)
		{
			if (mCapacity >= capacity)
				return;
			Type* pBuffer = mAllocator.Allocate(capacity);
			Assert(pBuffer != NULL, "Allocation failed");
			Copy(reinterpret_cast<char *>(mBegin), reinterpret_cast<char *>(mBegin) + mCapacity * sizeof(Type), reinterpret_cast<char *>(pBuffer));
			mAllocator.Deallocate(mBegin);
			mEnd = pBuffer + (mEnd - mBegin);
			mBegin = pBuffer;
			mCapacity = capacity;
		}

		size_t GetLength() const
		{
			return mEnd - mBegin;
		}

		size_t GetCapacity() const
		{
			return mCapacity;
		}

		void Clear()
		{
			for (ConstIterator i = Begin(); i != End(); ++i)
				mAllocator.Destroy(&(*i));
			mEnd = mBegin;
		}

		bool IsEmpty() const
		{
			return mEnd == mBegin;
		}

		ConstReference At(size_t index) const
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			return mBegin[index];
		}

		Reference Front()
		{
			Assert(mEnd > mBegin, "Empty vector");
			return mBegin[0];
		}

		Reference Back()
		{
			Assert(mEnd > mBegin, "Empty vector");
			return *(mEnd - 1);
		}

		void PushBack(ConstReference data)
		{
			if (mEnd >= mCapacity + mBegin)
				Allocate(mEnd - mBegin + mCapacity / 2 + 1);
			mAllocator.Construct(mEnd, data);
			mEnd++;
		}

		Type PopBack()
		{
			Assert(mEnd > mBegin, "Empty vector");
			mEnd--;
			Type result(*mEnd);
			mAllocator.Destroy(mEnd);
			return result;
		}

		void Erase(size_t index)
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			mAllocator.Destroy(mBegin + index);
			mBegin[index] = *(mEnd - 1);
			mEnd--;
		}

		void ErasePreserveOrder(size_t index)
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			mAllocator.Destroy(mBegin + index);
			for (Iterator i = mBegin + index; i != mEnd - 1; ++i)
				*i = *(i + 1);
			mEnd--;
		}

	private:
		/* Variables. */
		Pointer mBegin;
		Pointer mEnd;
		size_t mCapacity;
		Allocator mAllocator;
};

}

#endif /* COMMON_VECTOR_HPP */

/* EOF */
