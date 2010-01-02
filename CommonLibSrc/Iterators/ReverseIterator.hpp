#ifndef COMMON_REVERSE_ITERATOR_HPP
#define COMMON_REVERSE_ITERATOR_HPP

#include "../Internal.hpp"

namespace Common
{

template<class Iterator> class ReverseIterator
{
	public:
		typedef ReverseIterator<Iterator> MyType;
		typedef typename Iterator::ValueType ValueType;
		typedef typename Iterator::Pointer Pointer;
		typedef typename Iterator::Reference Reference;

		ReverseIterator()
		{
		}

		explicit ReverseIterator(Iterator iterator) : mBaseIterator(iterator)
		{
		}

		ReverseIterator(const MyType& iterator) : mBaseIterator(iterator.mBaseIterator)
		{
		}

		MyType& operator= (const MyType& iterator)
		{
			mBaseIterator = iterator.Base();
			return *this;
		}

		template <class ConstIterator> ReverseIterator(const ReverseIterator<ConstIterator>& iterator) : mBaseIterator(iterator.Base())
		{
		}

		template <class ConstIterator> MyType& operator= (const ReverseIterator<ConstIterator>& iterator)
		{
			mBaseIterator = iterator.Base();
			return *this;
		}

		Iterator Base() const
		{
			return mBaseIterator;
		}

		template <class ConstIterator> bool operator== (const ReverseIterator<ConstIterator>& iterator) const
		{
			return mBaseIterator == iterator.Base();
		}

		template <class ConstIterator> bool operator!= (const ReverseIterator<ConstIterator>& iterator) const
		{
			return mBaseIterator != iterator.Base();
		}

		Reference operator* () const
		{
			Iterator iterator = mBaseIterator;
			return *--iterator;
		}

		Pointer operator-> () const
		{
			return &(operator*());
		}

		MyType& operator++ ()
		{
			--mBaseIterator;
			return *this;
		}

		MyType operator++ (int)
		{
			MyType iterator = *this;
			--mBaseIterator;
			return iterator;
		}

		MyType& operator-- ()
		{
			++mBaseIterator;
			return *this;
		}

		MyType operator-- (int)
		{
			MyType iterator = *this;
			++mBaseIterator;
			return iterator;
		}

		MyType operator+ (ptrdiff_t amount) const
		{
			return MyType(mBaseIterator - amount);
		}

		MyType& operator+= (ptrdiff_t amount)
		{
			mBaseIterator -= amount;
			return *this;
		}

		MyType operator- (ptrdiff_t amount) const
		{
			return MyType(mBaseIterator + amount);
		}

		MyType& operator-= (ptrdiff_t amount)
		{
			mBaseIterator += amount;
			return *this;
		}

		Reference operator[] (ptrdiff_t index) const
		{
			return *(*this + index);
		}

	private:
		Iterator mBaseIterator;
		typedef ReverseIterator<Iterator> MyType;
};

}

#endif /* COMMON_REVERSE_ITERATOR_HPP */

/* EOF */
