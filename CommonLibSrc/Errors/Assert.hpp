#ifndef COMMON_ASSERT_HPP
#define COMMON_ASSERT_HPP

#include "../Internal.hpp"

namespace Common
{

#ifdef _DEBUG
void Assert(bool bExpression, const char *pReason);
#else
#define Assert(bExpression, pReason) ((void)0)
#endif /* DEBUG */

}

#endif /* COMMON_ASSERT_HPP */

/* EOF */
