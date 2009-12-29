#ifdef _DEBUG

#include "Assert.hpp"
#undef NDEBUG
#include <cassert>
#include <cstdio>

namespace Common
{

void Assert(bool expression, const char* reason)
{
	if (!expression)
		printf("%s\n", reason);
	assert(expression);
}

void AssertAlwaysExecute(bool expression, const char* reason)
{
	if (!expression)
		printf("%s\n", reason);
	assert(expression);
}


}

#endif /* DEBUG */

/* EOF */
