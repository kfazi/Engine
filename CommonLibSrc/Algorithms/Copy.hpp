#ifndef COMMON_COPY_HPP
#define COMMON_COPY_HPP

#include "../Internal.hpp"

namespace Common
{

template<class Input, class Output> void Copy(Input first, Input last, Output output)
{
	while (first != last)
	{
		*output = *first;
		first++;
		output++;
	}
}

}

#endif /* COMMON_COPY_HPP */

/* EOF */
