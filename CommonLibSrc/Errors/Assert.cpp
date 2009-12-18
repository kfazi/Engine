#ifdef _DEBUG

#include "Assert.hpp"
#undef NDEBUG
#include <cassert>

namespace Common
{

void Assert(bool bExpression, const char*)
{
	assert(bExpression);
}

void AssertAlwaysExecute(bool bExpression, const char*)
{
	assert(bExpression);
}


}

#endif /* DEBUG */

/* EOF */