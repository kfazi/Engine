#ifndef COMMON_STRING_ITERATOR_HPP
#define COMMON_STRING_ITERATOR_HPP

#include "../Internal.hpp"

namespace Common
{

template<typename TCharType>
class CStringIterator
{
	private:
		CStringBase<TCharType> *m_pOwner;
		unsigned int m_iIndex;

	public:
		CStringIterator()
};

}

#endif /* COMMON_STRING_ITERATOR_HPP */

/* EOF */
