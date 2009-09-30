#ifndef COMMON_COPY_HPP
#define COMMON_COPY_HPP

#include "../Internal.hpp"

namespace Common
{

template<class CInput, class COutput> void Copy(CInput cFirst, CInput cLast, COutput cOutput)
{
	while (cFirst != cLast)
	{
		*cOutput = *cFirst;
		cFirst++;
		cOutput++;
	}
}

}

#endif /* COMMON_COPY_HPP */

/* EOF */
