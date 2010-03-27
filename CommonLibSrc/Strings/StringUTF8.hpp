#ifndef COMMON_STRING_UTF8_HPP
#define COMMON_STRING_UTF8_HPP

#include "../Internal.hpp"
#include "StringBase.hpp"
#include "CharTypes.hpp"

namespace Common
{

class StringUTF16;
class StringUTF32;

class COMMONDLLIMPORTEXPORT StringUTF8: public StringBase<CharUTF8>
{
	public:
		typedef StringBase<CharUTF8> MyBase;

		StringUTF8();
		StringUTF8(size_t capacity);
		StringUTF8(const StringUTF32& stringUTF32);
		StringUTF8(const StringUTF16& stringUTF16);
		StringUTF8(const StringUTF8& stringUTF8);
		StringUTF8(const CharUTF32* plainString);
		StringUTF8(const CharUTF32* plainString, size_t length);
		StringUTF8(const CharUTF16* plainString);
		StringUTF8(const CharUTF16* plainString, size_t length);
		StringUTF8(const CharUTF8* plainString);
		StringUTF8(const CharUTF8* plainString, size_t length);

		StringUTF8& operator+= (const StringUTF32& string);
		StringUTF8& operator+= (const StringUTF16& string);
		StringUTF8& operator+= (const StringUTF8& string);
		StringUTF8& operator+= (const CharUTF32* plainString);
		StringUTF8& operator+= (const CharUTF16* plainString);
		StringUTF8& operator+= (const CharUTF8* plainString);
		StringUTF8& operator+= (CharUTF32 plainChar);
		StringUTF8& operator+= (CharUTF16 plainChar);
		StringUTF8& operator+= (CharUTF8 plainChar);
};

}

#endif /* COMMON_STRING_UTF8_HPP */

/* EOF */
