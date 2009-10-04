#ifndef COMMON_ASSERT_HPP
#define COMMON_ASSERT_HPP

#include "../Internal.hpp"
#include <cassert>

namespace Common
{

#ifdef DEBUG
void Assert(bool bExpression, char *pReason)
{
	::assert(bExpression);
}
#else
#define Assert(bExpression, pReason) ((void)0)
#endif /* DEBUG */

}

#endif /* COMMON_ASSERT_HPP */

/* EOF */
