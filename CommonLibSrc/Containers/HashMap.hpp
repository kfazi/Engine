/*!
 * \file HashMap.hpp
 *
 * \author kfazi
 * \date March 2010
 *
 * \link Common::HashMap HashMap\endlink class.
 */

#ifndef COMMON_HASH_MAP_HPP
#define COMMON_HASH_MAP_HPP

#include "../Internal.hpp"
#include "../Iterators/IteratorTags.hpp"
#include "../Iterators/ReverseIteratorBase.hpp"
#include "../Iterators/Advance.hpp"
#include "Pair.hpp"
#include "Vector.hpp"
#include "LinkedList.hpp"

namespace Common
{

template<class Type> struct Hash
{
	typename Type KeyType;
	size_t operator() (const Type data)
	{
	}
};

/*!
 * \class HashMap
 * \param KeyHashClass Key hashing class.
 * \param ValueType Type of contained data.
 * \param HashClassType Template hash class, that will be used to calculate hash value for keys.
 * \param Allocator Allocator used to allocate pair of key and value data.
 * \headerfile
 * \brief A hash map class.
 *
 * \author kfazi
 * \date March 2010
 */
template<class KeyType, class ValueType, template<typename> class HashClassType = Hash,
	class Allocator = DefaultAllocator<Pair<KeyType, ValueType> > > class HashMap
{
	public:
		/*!
		 * \class IteratorBase
		 * \param Type Type of values in hash map.
		 * \param NonConstType Non-const type of Type.
		 * \param ConstType Const type of Type.
		 * \headerfile
		 * \brief An iterator base for HashMap class.
		 *
		 *
		 * \author kfazi
		 * \date March 2010
		 */
		template<typename Type, typename NonConstType, typename ConstType, typename ChainType,
			typename BucketType, typename ChainIteratorType, typename NonConstChainIteratorType,
			typename ConstChainIteratorType, typename BucketIteratorType,
			typename NonConstBucketIteratorType, typename ConstBucketIteratorType>
			class IteratorBase : public BidirectionalIteratorTag<Type, Type*, Type&>
		{
			friend class IteratorBase<NonConstType, NonConstType, ConstType, ChainType, BucketType,
				NonConstChainIteratorType, NonConstChainIteratorType, ConstChainIteratorType,
				NonConstBucketIteratorType, NonConstBucketIteratorType,
				ConstBucketIteratorType>; /*!< Non-const iterator. */
			friend class IteratorBase<ConstType, NonConstType, ConstType, ChainType, BucketType,
				ConstChainIteratorType, NonConstChainIteratorType, ConstChainIteratorType,
				ConstBucketIteratorType, NonConstBucketIteratorType,
				ConstBucketIteratorType>; /*!< Const iterator. */

			public:
				typedef IteratorBase<NonConstType, NonConstType, ConstType, ChainType, BucketType,
					NonConstChainIteratorType, NonConstChainIteratorType, ConstChainIteratorType,
					NonConstBucketIteratorType, NonConstBucketIteratorType,
					ConstBucketIteratorType> NonConstIteratorType;
				typedef IteratorBase<ConstType, NonConstType, ConstType, ChainType, BucketType,
					ConstChainIteratorType, NonConstChainIteratorType, ConstChainIteratorType,
					ConstBucketIteratorType, NonConstBucketIteratorType,
					ConstBucketIteratorType> ConstIteratorType;
				typedef IteratorBase<Type, NonConstType, ConstType, ChainType, BucketType,
					ChainIteratorType, NonConstChainIteratorType, ConstChainIteratorType,
					BucketIteratorType, NonConstBucketIteratorType, ConstBucketIteratorType> MyType;
				/*!
				 * Constructor.
				 *
				 * \param[in] address Address of current element.
				 */
				explicit IteratorBase(const BucketType* bucket, const BucketIteratorType& bucketIterator,
					const ChainIteratorType& chainIterator) : mBucket(bucket),
					mBucketIterator(bucketIterator), mChainIterator(chainIterator)
				{
				}

				/*!
				 * Constructor.
				 */
				IteratorBase()
				{
				}

				/*!
				 * Copy constructor.
				 *
				 * \param[in] iterator An iterator to copy from.
				 */
				IteratorBase(const NonConstIteratorType& iterator) :
					mBucket(iterator.mBucket), mBucketIterator(iterator.mBucketIterator),
					mChainIterator(iterator.mChainIterator)
				{
				}

				/*!
				 * Assignment operator.
				 *
				 * \return Current iterator.
				 */
				MyType& operator= (const MyType& iterator)
				{
					mBucket = iterator.mBucket;
					mBucketIterator = iterator.mBucketIterator;
					mChainIterator = iterator.mChainIterator;
					return *this;
				}

				/*!
				 * Increments iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				MyType& operator++ ()
				{
					++mChainIterator;
					while (mChainIterator == (*mBucketIterator).End())
					{
						Assert(mBucketIterator != mBucket->End(), "Iterator out of range");
						++mBucketIterator;
						if (mBucketIterator == mBucket->End())
						{
							--mBucketIterator;
							mChainIterator = (*mBucketIterator).End();
							return *this;
						}
						mChainIterator = (*mBucketIterator).Begin();
					}
					return *this;
				}

				/*!
				 * Increments iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				MyType& operator++ (int)
				{
					MyType iterator = *this;
					++(*this);
					return iterator;
				}

				/*!
				 * Decrements iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				MyType& operator-- ()
				{
					Assert(mChainIterator != (*mBucketIterator).Begin() ||
						mBucketIterator != mBucket->Begin(), "Iterator out of range");
					while (mChainIterator == (*mBucketIterator).Begin())
					{
						--mBucketIterator;
						mChainIterator = (*mBucketIterator).End();
						if (mBucketIterator == mBucket->Begin())
							break;
					}
					if (mChainIterator != (*mBucketIterator).Begin())
						--mChainIterator;
					return *this;
				}

				/*!
				 * Decrements iterator position by 1.
				 *
				 * \return Current iterator.
				 */
				MyType& operator-- (int)
				{
					MyType iterator = *this;
					--(*this);
					return iterator;
				}

				/*!
				 * Comparison operator.
				 *
				 * \param[in] iterator An iterator to compare to.
				 * \return True if iterators are equal.
				 */
				bool operator== (const ConstIteratorType& iterator) const
				{
					return mBucketIterator == iterator.mBucketIterator &&
						mChainIterator == iterator.mChainIterator;
				}

				/*!
				 * Comparison operator.
				 *
				 * \param[in] iterator An iterator to compare to.
				 * \return True if iterators differ.
				 */
				bool operator!= (const ConstIteratorType& iterator) const
				{
					return !(*this == iterator);
				}

				/*!
				 * Returns current element.
				 *
				 * \return Current element.
				 */
				Reference operator* () const
				{
					return *mChainIterator;
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
				const BucketType* mBucket;
				BucketIteratorType mBucketIterator;
				ChainIteratorType mChainIterator;
		};

		/* Typedefs. */
		typedef HashClassType<KeyType> HashClass;
		typedef HashMap<KeyType, ValueType, HashClassType, Allocator>
			MyType; /*!< This hash map type. */
		typedef Pair<KeyType, ValueType> ElementType;
		typedef LinkedList<ElementType, Allocator> ChainType;
		typedef Vector<ChainType> BucketType;
		typedef typename ChainType::Iterator ChainIteratorType;
		typedef typename ChainType::ConstIterator ChainConstIteratorType;
		typedef typename BucketType::Iterator BucketIteratorType;
		typedef typename BucketType::ConstIterator BucketConstIteratorType;
		typedef const ElementType& ConstReference; /*<! Constant reference. */
		typedef ElementType& Reference; /*!< Reference. */
		typedef const ElementType* ConstPointer; /*<! Constant pointer. */
		typedef ElementType* Pointer; /*<! Pointer. */
		typedef const ValueType& ValueConstReference; /*<! Constant reference to value. */
		typedef ValueType& ValueReference; /*!< Reference to value. */
		typedef const ValueType* ValueConstPointer; /*<! Constant pointer to value. */
		typedef ValueType* ValuePointer; /*<! Pointer to value. */
		typedef IteratorBase<const ElementType, ElementType, const ElementType, ChainType, BucketType,
			ChainConstIteratorType, ChainIteratorType, ChainConstIteratorType, BucketConstIteratorType,
			BucketIteratorType, BucketConstIteratorType> ConstIterator; /*!< Constant iterator. */
		typedef IteratorBase<ElementType, ElementType, const ElementType, ChainType, BucketType,
			ChainIteratorType, ChainIteratorType, ChainConstIteratorType, BucketIteratorType,
			BucketIteratorType, BucketConstIteratorType> Iterator; /*!< Constant iterator. */
		typedef ReverseIteratorBase<Iterator> ReverseIterator; /*!< Reverse iterator. */
		typedef ReverseIteratorBase<ConstIterator>
			ConstReverseIterator; /*!< Constant reverse iterator. */

		HashMap() : mBucket(251), mCapacity(251)
		{
			mBucket.Resize(251, ChainType());
		}

		HashMap(size_t capacity) : mBucket(capacity), mCapacity(capacity)
		{
			mBucket.Resize(capacity, ChainType());
		}

		HashMap(const MyType& hashMap)
		{
			mBucket = hashMap.mBucket;
			mLoad = hashMap.mLoad;
			mCapacity = hashMap.mCapacity;
		}

		~HashMap()
		{
		}

		/*!
		 * Returns iterator pointing to first element.
		 *
		 * \return Iterator pointing to first element.
		 */
		Iterator Begin()
		{
			BucketIteratorType iterator = mBucket.Begin();
			while ((*iterator).Begin() == (*iterator).End() && iterator != mBucket.End())
				++iterator;
			return Iterator(&mBucket, iterator, (*iterator).Begin());
		}

		/*!
		 * Returns iterator pointing to first element.
		 *
		 * \return Iterator pointing to first element.
		 */
		ConstIterator Begin() const
		{
			BucketConstIteratorType iterator = mBucket.Begin();
			while ((*iterator).Begin() == (*iterator).End() && iterator != mBucket.End())
				++iterator;
			return ConstIterator(&mBucket, iterator, (*iterator).Begin());
		}

		/*!
		 * Returns iterator pointing to after the last element.
		 *
		 * \return Iterator pointing to after the last element.
		 */
		Iterator End()
		{
			BucketIteratorType iterator = mBucket.Begin();
			//Advance(iterator, mCapacity);
			iterator += mCapacity - 1;
			return Iterator(&mBucket, iterator, (*iterator).End());
		}

		/*!
		 * Returns iterator pointing to after the last element.
		 *
		 * \return Iterator pointing to after the last element.
		 */
		ConstIterator End() const
		{
			BucketConstIteratorType iterator = mBucket.Begin();
			//Advance(iterator, mCapacity);
			iterator += mCapacity - 1;
			return ConstIterator(&mBucket, iterator, (*iterator).End());
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

		size_t GetLoad() const
		{
			return mLoad;
		}

		size_t GetCapacity() const
		{
			return mCapacity;
		}

		void Clear()
		{
			mLoad = 0;
			mBucket.Clear();
		}

		bool IsEmpty() const
		{
			return mLoad == 0;
		}

		ValueReference operator[] (const KeyType& key)
		{
			size_t hash = GetHash(key);
			for (ChainIteratorType iterator = mBucket[hash].Begin(); iterator != mBucket[hash].End();
				++iterator)
			{
				if ((*iterator).first == key)
					return (*iterator).second;
			}
			mLoad++;
			return (*Insert(MakePair(key, ValueType())));
		}

		ValueConstReference operator[] (const KeyType& key) const
		{
			size_t hash = GetHash(key);
			for (ChainIteratorType iterator = mBucket[hash].Begin(); iterator != mBucket[hash].End();
				++iterator)
			{
				if ((*iterator).first == key)
					return (*iterator).second;
			}
			Assert(false, "Key not found");
		}

		MyType& operator= (const MyType& hashMap)
		{
			return *this;
		}

		ValueReference Get(const KeyType& key)
		{
			Assert(mLoad > 0, "Empty hash map");
			size_t hash = GetHash(key);
			for (ChainIteratorType iterator = mBucket[hash].Begin(); iterator != mBucket[hash].End();
				++iterator)
			{
				if ((*iterator).first == key)
					return (*iterator).second;
			}
		}

		bool Contains(const KeyType& key) const
		{
			size_t hash = GetHash(key);
			for (ChainConstIteratorType iterator = mBucket[hash].Begin(); iterator != mBucket[hash].End();
				++iterator)
			{
				if ((*iterator).first == key)
					return true;
			}
			return false;
		}

		Iterator Insert(const ElementType& value)
		{
			Assert(!Contains(value.first), "Key already exists");
			mLoad++;
			size_t hash = GetHash(value.first);
			return Iterator(&mBucket, mBucket.Begin() + hash, mBucket[hash].PushBack(value));
		}

		Iterator Erase(const KeyType& key)
		{
			Assert(mLoad > 0, "Empty hash map");
			Assert(Contains(key), "Key not found");
			mLoad--;
			size_t hash = GetHash(key);
			for (ChainIteratorType iterator = mBucket[hash].Begin(); iterator != mBucket[hash].End();
				++iterator)
			{
				if ((*iterator).first == key)
					return Iterator(&mBucket, mBucket.Begin() + hash, mBucket[hash].Erase(iterator));
			}
		}

	private:
		size_t GetHash(const KeyType& key) const
		{
			size_t hash = HashClass()(key);
			hash %= mCapacity;
			return hash;
		}

		BucketType mBucket;
		size_t mLoad;
		size_t mCapacity;
};

}

#endif /* COMMON_HASH_MAP_HPP */

/* EOF */
