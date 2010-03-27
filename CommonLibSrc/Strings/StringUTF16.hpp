#ifndef COMMON_STRING_UTF16_HPP
#define COMMON_STRING_UTF16_HPP

#include "../Internal.hpp"
#include "StringBase.hpp"
#include "CharTypes.hpp"

namespace Common
{

class StringUTF8;
class StringUTF32;

class COMMONDLLIMPORTEXPORT StringUTF16: public StringBase<CharUTF16>
{
	private:
		typedef StringBase<CharUTF16> MyBase;

	public:
		StringUTF16();
		StringUTF16(size_t capacity);
		StringUTF16(const StringUTF32& stringUTF32);
		StringUTF16(const StringUTF16& stringUTF16);
		StringUTF16(const StringUTF8& stringUTF8);
		StringUTF16(const CharUTF32* plainString);
		StringUTF16(const CharUTF32* plainString, size_t length);
		StringUTF16(const CharUTF16* plainString);
		StringUTF16(const CharUTF16* plainString, size_t length);
		StringUTF16(const CharUTF8* plainString);
		StringUTF16(const CharUTF8* plainString, size_t length);

		StringUTF16& operator+= (const StringUTF32& string);
		StringUTF16& operator+= (const StringUTF16& string);
		StringUTF16& operator+= (const StringUTF8& string);
		StringUTF16& operator+= (const CharUTF32* plainString);
		StringUTF16& operator+= (const CharUTF16* plainString);
		StringUTF16& operator+= (const CharUTF8* plainString);
		StringUTF16& operator+= (CharUTF32 plainChar);
		StringUTF16& operator+= (CharUTF16 plainChar);
		StringUTF16& operator+= (CharUTF8 plainChar);
};

}

#endif /* COMMON_STRING_UTF16_HPP */

/* EOF */
