#ifndef COMMON_STRING_STATIC_HPP
#define COMMON_STRING_STATIC_HPP

#include "../Internal.hpp"

namespace Common
{

class CStringStatic
{
	private:
		static const unsigned int m_sBaseCapacity;

	protected:
		static unsigned int GetBaseCapacity()
		{
			return m_sBaseCapacity;
		}
};

}

#endif /* COMMON_STRING_STATIC_HPP */

/* EOF */
