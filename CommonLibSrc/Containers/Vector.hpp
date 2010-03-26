/*!
 * \file Vector.hpp
 *
 * \author kfazi
 * \date February 2010
 *
 * \link Common::Vector Vector\endlink class.
 */

#ifndef COMMON_VECTOR_HPP
#define COMMON_VECTOR_HPP

#include "../Internal.hpp"
#include "../Algorithms/Copy.hpp"
#include "../Iterators/IteratorTags.hpp"
#include "../Iterators/ReverseIteratorBase.hpp"

namespace Common
{

/*!
 * \class Vector
 * \param Type Type of contained data.
 * \param Allocator Allocator used to allocate contained data.
 * \headerfile
 * \brief A vector class.
 *
 *
 * This is equivalent of std::vector.
 *
 * Two main differences are:
 * - Erase() doesn't preserve order, if you want to preserve order use ErasePreserveOrder().
 * - For most algorithms you should use ranges (through GetRange()) instead of iterators.
 *
 * \author kfazi
 * \date February 2010
 */
template<class Type, class Allocator = DefaultAllocator<Type> > class Vector
{
	public:
		/*!
		 * \class IteratorBase
		 * \param Type Type of data in vector.
		 * \param NonConstType Non-const type of Type.
		 * \param ConstType Const type of Type.
		 * \headerfile
		 * \brief An iterator base for Vector class.
		 *
		 *
		 * \author kfazi
		 * \date February 2010
		 */
		template<typename Type, typename NonConstType, typename ConstType> class IteratorBase : public RandomAccessIteratorTag<Type, Type*, Type&>
		{
			friend class IteratorBase<NonConstType, NonConstType, ConstType>; /*!< Non-const iterator. */
			friend class IteratorBase<ConstType, NonConstType, ConstType>; /*!< Const iterator. */

			public:
				/*!
				 * Constructor.
				 *
				 * \param[in] address Address of current element.
				 */
				explicit IteratorBase(Type* address) : mAddress(address)
				{
				}

				/*!
				 * Constructor.
				 */
				IteratorBase() : mAddress(NULL)
				{
				}

				/*!
				 * Copy constructor.
				 *
				 * \param[in] iterator An iterator to copy from.
				 */
				IteratorBase(const IteratorBase<NonConstType, NonConstType, ConstType>& iterator) : mAddress(iterator.mAddress)
				{
				}

				/*!
				 * Increments iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				IteratorBase& operator++ ()
				{
					mAddress++;
					return *this;
				}

				/*!
				 * Increments iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				IteratorBase& operator++ (int)
				{
					IteratorBase<Type, NonConstType, ConstType> iterator = *this;
					mAddress++;
					return iterator;
				}

				/*!
				 * Decrements iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				IteratorBase& operator-- ()
				{
					mAddress--;
					return *this;
				}

				/*!
				 * Decrements iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				IteratorBase& operator-- (int)
				{
					IteratorBase<Type, NonConstType, ConstType> iterator = *this;
					mAddress--;
					return iterator;
				}

				/*!
				 * Increments iterator position by amount.
				 *
				 * \param[in] amount Amount of elements to skip.
				 *
				 * \return Incremented iterator.
				 */
				IteratorBase operator+ (ptrdiff_t amount) const
				{
					return IteratorBase(mAddress + amount);
				}

				/*!
				 * Increments iterator position by amount.
				 *
				 * \param[in] amount Amount of elements to skip.
				 *
				 * \return Current iterator.
				 */
				IteratorBase& operator+= (ptrdiff_t amount)
				{
					mAddress += amount;
					return *this;
				}

				/*!
				 * Decrements iterator position by amount.
				 *
				 * \param[in] amount Amount of elements to skip.
				 *
				 * \return Decremented iterator.
				 */
				IteratorBase operator- (ptrdiff_t amount) const
				{
					return IteratorBase(mAddress - amount);
				}

				/*!
				 * Decrements iterator position by amount.
				 *
				 * \param[in] amount Amount of elements to skip.
				 *
				 * \return Current iterator.
				 */
				IteratorBase& operator-= (ptrdiff_t amount)
				{
					mAddress -= amount;
					return *this;
				}

				/*!
				 * Returns index element after current one.
				 *
				 * \param[in] index Amount of elements to skip.
				 *
				 * \return Element.
				 */
				Reference operator[] (ptrdiff_t index) const
				{
					return *(mAddress + index);
				}

				/*!
				 * Comparison operator.
				 *
				 * \param[in] iterator An iterator to compare to.
				 * \return True if iterators are equal.
				 */
				bool operator== (const IteratorBase<ConstType, NonConstType, ConstType>& iterator) const
				{
					return mAddress == iterator.mAddress;
				}

				/*!
				 * Comparison operator.
				 *
				 * \param[in] iterator An iterator to compare to.
				 * \return True if iterators differ.
				 */
				bool operator!= (const IteratorBase<ConstType, NonConstType, ConstType>& iterator) const
				{
					return mAddress != iterator.mAddress;
				}

				/*!
				 * Returns current element.
				 *
				 * \return Current element.
				 */
				Reference operator* () const
				{
					return *mAddress;
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
				Type* mAddress; /*!< Pointer to current element. */
		};

		/* Typedefs. */
		typedef Vector<Type, Allocator> MyType; /*!< This vector type. */
		typedef const Type& ConstReference; /*<! Constant reference. */
		typedef Type& Reference; /*!< Reference. */
		typedef const Type* ConstPointer; /*<! Constant pointer. */
		typedef Type* Pointer; /*<! Pointer. */
		typedef IteratorBase<const Type, Type, const Type> ConstIterator; /*!< Constant iterator. */
		typedef IteratorBase<Type, Type, const Type> Iterator; /*!< Iterator. */
		typedef ReverseIteratorBase<Iterator> ReverseIterator; /*!< Reverse iterator. */
		typedef ReverseIteratorBase<ConstIterator>
			ConstReverseIterator; /*!< Constant reverse iterator. */

		/*!
		 * Constructor.
		 */
		Vector(): mBegin(NULL), mEnd(NULL), mCapacity(0)
		{
		}

		/*!
		 * Constructor.
		 *
		 * \param[in] capacity Initial capacity.
		 */
		Vector(size_t capacity): mBegin(Allocator::Allocate(capacity)), mCapacity(capacity)
		{
			Assert(mBegin != NULL, "Allocation failed");
			mEnd = mBegin;
		}

		/*!
		 * Copy constructor.
		 *
		 * \param[in] vector A vector to copy from.
		 */
		Vector(const Vector& vector): mBegin(NULL), mEnd(NULL), mCapacity(0)
		{
			*this = vector;
		}

		/*!
		 * Destructor.
		 */
		~Vector()
		{
			Clear();
			Allocator::Deallocate(mBegin);
		}

		/*!
		 * Assignment operator.
		 *
		 * \param[in] vector A vector to copy from.
		 * \return Actual vector.
		 */
		MyType& operator= (const MyType& vector)
		{
			size_t iNewCapacity = vector.mCapacity;
			if (iNewCapacity > mCapacity)
				Allocate(iNewCapacity);
			Copy(vector.mBegin, vector.mEnd, mBegin);
			mEnd = mBegin + (vector.mEnd - vector.mBegin);
			return *this;
		}

		/*!
		 * Resizes vector.
		 *
		 * If size is smaller than actual length the vector is shrinked.
		 * If size is larger than actual length the vector is filled up with data.
		 * \param[in] size Desired size of the vector.
		 * \param[in] data Data to fill the vector with.
		 */
		void Resize(size_t size, ConstReference data)
		{
			Allocate(size);
			while (size < GetLength())
			{
				mEnd--;
				Allocator::Destroy(mEnd);
			}
			while (size > GetLength())
			{
				Allocator::Construct(mEnd, data);
				mEnd++;
			}
		}

		/*!
		 * Returns index element in vector.
		 *
		 * \param[in] index Index of element.
		 * \return Element.
		 */
		Reference operator[] (size_t index)
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			return mBegin[index];
		}

		/*!
		 * Returns index element in vector.
		 *
		 * \param[in] index Index of element.
		 * \return Element.
		 */
		ConstReference operator[] (size_t index) const
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			return mBegin[index];
		}

		/*!
		 * Returns iterator pointing to first element.
		 *
		 * \return Iterator pointing to first element.
		 */
		Iterator Begin()
		{
			return Iterator(mBegin);
		}

		/*!
		 * Returns iterator pointing to first element.
		 *
		 * \return Iterator pointing to first element.
		 */
		ConstIterator Begin() const
		{
			return ConstIterator(mBegin);
		}

		/*!
		 * Returns iterator pointing to after the last element.
		 *
		 * \return Iterator pointing to after the last element.
		 */
		Iterator End()
		{
			return Iterator(mEnd);
		}

		/*!
		 * Returns iterator pointing to after the last element.
		 *
		 * \return Iterator pointing to after the last element.
		 */
		ConstIterator End() const
		{
			return ConstIterator(mEnd);
		}

		/*!
		 * Returns iterator pointing to the last element.
		 *
		 * \return Iterator pointing to the last element.
		 */
		ReverseIterator ReverseBegin()
		{
			return ReverseIterator(Iterator(mEnd));
		}

		/*!
		 * Returns iterator pointing to the last element.
		 *
		 * \return Iterator pointing to the last element.
		 */
		ConstReverseIterator ReverseBegin() const
		{
			return ConstReverseIterator(ConstIterator(mEnd));
		}

		/*!
		 * Returns iterator pointing to one before first element.
		 *
		 * \return Iterator pointing to one before first element.
		 */
		ReverseIterator ReverseEnd()
		{
			return ReverseIterator(Iterator(mBegin));
		}

		/*!
		 * Returns iterator pointing to one before first element.
		 *
		 * \return Iterator pointing to one before first element.
		 */
		ConstReverseIterator ReverseEnd() const
		{
			return ConstReverseIterator(ConstIterator(mBegin));
		}

		/*!
		 * Allocates new memory for vector if requested capacity is larger than current buffer size.
		 *
		 * \param[in] capacity New buffer size.
		 */
		void Allocate(size_t capacity)
		{
			if (mCapacity >= capacity)
				return;
			Type* pBuffer = Allocator::Allocate(capacity);
			Assert(pBuffer != NULL, "Allocation failed");
			Copy(reinterpret_cast<char *>(mBegin), reinterpret_cast<char *>(mBegin) + mCapacity * sizeof(Type), reinterpret_cast<char *>(pBuffer));
			Allocator::Deallocate(mBegin);
			mEnd = pBuffer + (mEnd - mBegin);
			mBegin = pBuffer;
			mCapacity = capacity;
		}

		/*!
		 * Returns amount of elements in vector.
		 *
		 * \return Current length.
		 */
		size_t GetLength() const
		{
			return mEnd - mBegin;
		}

		/*!
		 * Returns possible amount of elements in vector, which doesn't require reallocation.
		 *
		 * \return Current capacity.
		 */
		size_t GetCapacity() const
		{
			return mCapacity;
		}

		/*!
		 * Removes all elements.
		 */
		void Clear()
		{
			for (ConstIterator i = Begin(); i != End(); ++i)
				Allocator::Destroy(&(*i));
			mEnd = mBegin;
		}

		/*!
		 * Checks if vector contains some elements.
		 *
		 * \return True if vector is empty.
		 */
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
			Allocator::Construct(mEnd, data);
			mEnd++;
		}

		Type PopBack()
		{
			Assert(mEnd > mBegin, "Empty vector");
			mEnd--;
			Type result(*mEnd);
			Allocator::Destroy(mEnd);
			return result;
		}

		void Erase(size_t index)
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			Allocator::Destroy(mBegin + index);
			*(mBegin + index) = *(mEnd - 1);
			mEnd--;
		}

		void ErasePreserveOrder(size_t index)
		{
			Assert(mEnd > index + mBegin, "Index out of bounds");
			Allocator::Destroy(mBegin + index);
			for (Iterator i = Begin() + index; i != End() - 1; ++i)
				*i = *(i + 1);
			mEnd--;
		}

	private:
		/* Variables. */
		Pointer mBegin;
		Pointer mEnd;
		size_t mCapacity;
};

}

#endif /* COMMON_VECTOR_HPP */

/* EOF */
