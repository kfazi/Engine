#ifndef COMMON_REVERSE_ITERATOR_HPP
#define COMMON_REVERSE_ITERATOR_HPP

#include "../Internal.hpp"

namespace Common
{

template<class Iterator> class ReverseIterator
{
	public:
		ReverseIterator()
		{
		}

		explicit ReverseIterator(iterator_type __x) : current(__x)
		{
		}

		ReverseIterator(const _Self& __x) : current(__x.current)
		{
		}

		_Self& operator= (const _Self& __x)
		{
			current = __x.base();
			return *this;
		}
#  if defined (_STLP_MEMBER_TEMPLATES)
		template <class _Iter>
		reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {}
		template <class _Iter>
		_Self& operator = (const reverse_iterator<_Iter>& __x) { current = __x.base(); return *this; }
#  endif /* _STLP_MEMBER_TEMPLATES */

		iterator_type base() const
		{
			return current;
		}

		reference operator* () const
		{
			_Iterator __tmp = current;
			return *--__tmp;
		}

		_STLP_DEFINE_ARROW_OPERATOR
			_Self& operator++ ()
		{
				--current;
				return *this;
		}

		_Self operator++ (int)
		{
			_Self __tmp = *this;
			--current;
			return __tmp;
		}

		_Self& operator-- ()
		{
			++current;
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			++current;
			return __tmp;
		}

		_Self operator+ (difference_type __n) const
		{
			return _Self(current - __n);
		}

		_Self& operator+= (difference_type __n)
		{
			current -= __n;
			return *this;
		}

		_Self operator- (difference_type __n) const
		{
			return _Self(current + __n);
		}

		_Self& operator-= (difference_type __n)
		{
			current += __n;
			return *this;
		}

		reference operator[] (difference_type __n) const
		{
			return *(*this + __n);
		}
};

}

#endif /* COMMON_REVERSE_ITERATOR_HPP */

/* EOF */
