#ifndef COMMON_STRING_ITERATOR_HPP
#define COMMON_STRING_ITERATOR_HPP

#include "../Internal.hpp"

namespace Common
{

template<typename CharType>
class StringIterator
{
	private:
		StringBase<CharType> *m_pOwner;
		unsigned int m_iIndex;

	public:
		StringIterator()
};

}

#endif /* COMMON_STRING_ITERATOR_HPP */

/* EOF */
