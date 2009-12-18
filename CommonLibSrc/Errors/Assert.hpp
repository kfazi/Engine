#ifndef COMMON_ASSERT_HPP
#define COMMON_ASSERT_HPP

#include "../Internal.hpp"

namespace Common
{

/* Run-time assert */
#ifdef _DEBUG
void COMMONDLLIMPORTEXPORT Assert(bool bExpression, const char* pReason);
void COMMONDLLIMPORTEXPORT AssertAlwaysExecute(bool bExpression, const char* pReason);
#else
#define Assert(bExpression, pReason) ((void)0)
#define AssertAlwaysExecute(bExpression, pReason) (bExpression)
#endif /* _DEBUG */

/* Compile-time assert */
namespace StaticCheck
{

template<bool> struct SCheck
{
	inline SCheck()
	{
	}
};

template<> struct SCheck<false>;

}

/* Note we need the 2 con cats below because arguments to ##
 * are not expanded, so we need to expand __LINE__ with one indirection
 * before doing the actual concatenation. */
#define STATIC_ASSERT_JOIN(x, y) STATIC_ASSERT_JOIN_AGAIN(x, y)
#define STATIC_ASSERT_JOIN_AGAIN(x, y) x ## y

#define StaticAssert(bExpression, Reason) \
	StaticCheck::SCheck<(bExpression != 0)> \
	STATIC_ASSERT_JOIN(STATIC_ASSERT_JOIN(ERROR__, __LINE__), STATIC_ASSERT_JOIN(__, Reason))

}

#endif /* COMMON_ASSERT_HPP */

/* EOF */
