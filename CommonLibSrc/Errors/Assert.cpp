#ifdef _DEBUG

#include "Assert.hpp"
#undef NDEBUG
#ifdef MSVC
#include <intrin.h>
#else
#include <cassert>
#endif /* MSVC */
#include <cstdio>

namespace Common
{

void Assert(bool expression, const char* reason)
{
	if (!expression)
		printf("%s\n", reason);
#ifdef MSVC
	if (!expression)
		__debugbreak();
#else
	assert(expression);
#endif /* MSVC */
}

void AssertAlwaysExecute(bool expression, const char* reason)
{
	if (!expression)
		printf("%s\n", reason);
#ifdef MSVC
	if (!expression)
		__debugbreak();
#else
	assert(expression);
#endif /* MSVC */
}


}

#endif /* DEBUG */

/* EOF */
