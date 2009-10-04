#ifndef COMMON_STRING_HPP
#define COMMON_STRING_HPP

#include "../Internal.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"

namespace Common
{

#if COMMONLIB_STRING_CHAR == UTF32
typedef TCharUTF32 TChar;
typedef CStringUTF32 CString;
#elif COMMONLIB_STRING_CHAR == UTF16
typedef TCharUTF16 TChar;
typedef CStringUTF16 CString;
#else
#error Wrong COMMONLIB_STRING_CHAR value.
#endif /* COMMONLIB_STRING_CHAR */

}

#endif /* COMMON_STRING_HPP */

/* EOF */
