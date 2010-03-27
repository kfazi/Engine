#ifndef COMMON_STRING_UTF32_HPP
#define COMMON_STRING_UTF32_HPP

#include "../Internal.hpp"
#include "StringBase.hpp"
#include "CharTypes.hpp"

namespace Common
{

class StringUTF8;
class StringUTF16;

class COMMONDLLIMPORTEXPORT StringUTF32: public StringBase<CharUTF32>
{
	private:
		typedef StringBase<CharUTF32> MyBase;

	public:
		StringUTF32();
		StringUTF32(size_t capacity);
		StringUTF32(const StringUTF32& stringUTF32);
		StringUTF32(const StringUTF16& stringUTF16);
		StringUTF32(const StringUTF8& stringUTF8);
		StringUTF32(const CharUTF32* plainString);
		StringUTF32(const CharUTF32* plainString, size_t length);
		StringUTF32(const CharUTF16* plainString);
		StringUTF32(const CharUTF16* plainString, size_t length);
		StringUTF32(const CharUTF8* plainString);
		StringUTF32(const CharUTF8* plainString, size_t length);

		StringUTF32& operator+= (const StringUTF32& string);
		StringUTF32& operator+= (const StringUTF16& string);
		StringUTF32& operator+= (const StringUTF8& string);
		StringUTF32& operator+= (const CharUTF32* plainString);
		StringUTF32& operator+= (const CharUTF16* plainString);
		StringUTF32& operator+= (const CharUTF8* plainString);
		StringUTF32& operator+= (CharUTF32 plainChar);
		StringUTF32& operator+= (CharUTF16 plainChar);
		StringUTF32& operator+= (CharUTF8 plainChar);

		StringUTF32 ToUpper() const;
		StringUTF32 ToLower() const;
};

}

#endif /* COMMON_STRING_UTF32_HPP */

/* EOF */
