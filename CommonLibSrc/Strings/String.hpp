#ifndef COMMON_STRING_HPP
#define COMMON_STRING_HPP

#include "../Internal.hpp"
#include "StringUTF16.hpp"
#include "StringUTF32.hpp"

namespace Common
{

#if COMMONLIB_STRING_CHAR == UTF32
typedef CharUTF32 Char;
typedef StringUTF32 String;
#elif COMMONLIB_STRING_CHAR == UTF16
typedef CharUTF16 Char;
typedef StringUTF16 String;
#else
#error Wrong COMMONLIB_STRING_CHAR value.
#endif /* COMMONLIB_STRING_CHAR */

}

#endif /* COMMON_STRING_HPP */

/* EOF */
