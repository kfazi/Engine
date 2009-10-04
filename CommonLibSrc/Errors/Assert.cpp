#ifdef _DEBUG

#include "Assert.hpp"
#undef NDEBUG
#include <cassert>

namespace Common
{

void Assert(bool bExpression, const char *pReason)
{
	assert(bExpression);
}

}

#endif /* DEBUG */

/* EOF */
