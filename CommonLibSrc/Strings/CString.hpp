#ifndef COMMON_STRING_HPP
#define COMMON_STRING_HPP

#include "../Internal.hpp"
#include "CStringBase.hpp"

namespace Common
{

#if COMMONLIB_STRING_CHAR == UTF32
typedef unsigned int TChar;
#elif COMMONLIB_STRING_CHAR == UTF16
typedef unsigned short TChar;
#else
#error Wrong COMMONLIB_STRING_CHAR value.
#endif /* COMMONLIB_STRING_CHAR */

typedef CStringBase<TChar> CString;

}

#endif /* COMMON_STRING_HPP */

/* EOF */
