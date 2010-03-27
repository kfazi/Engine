#include "StringUTF8.hpp"
#include "StringUTF16.hpp"
#include "StringUTF32.hpp"
#include "UTFConvert.hpp"

namespace Common
{

StringUTF16::StringUTF16(): MyBase()
{
}

StringUTF16::StringUTF16(size_t capacity): MyBase(capacity)
{
}

StringUTF16::StringUTF16(const StringUTF32& stringUTF32): MyBase()
{
	UTFConvert::FromUTF32ToUTF16(*this, stringUTF32);	
}

StringUTF16::StringUTF16(const StringUTF16& stringUTF16): MyBase(stringUTF16)
{
}

StringUTF16::StringUTF16(const StringUTF8& stringUTF8): MyBase()
{
	UTFConvert::FromUTF8ToUTF16(*this, stringUTF8);	
}

StringUTF16::StringUTF16(const CharUTF32* plainString): MyBase()
{
	UTFConvert::FromUTF32ToUTF16(*this, StringUTF32(plainString));
}

StringUTF16::StringUTF16(const CharUTF32* plainString, size_t length): MyBase()
{
	UTFConvert::FromUTF32ToUTF16(*this, StringUTF32(plainString, length));
}

StringUTF16::StringUTF16(const CharUTF16* plainString): MyBase(plainString)
{
}

StringUTF16::StringUTF16(const CharUTF16* plainString, size_t length): MyBase(plainString, length)
{
}

StringUTF16::StringUTF16(const CharUTF8* plainString): MyBase()
{
	UTFConvert::FromUTF8ToUTF16(*this, StringUTF8(plainString));	
}

StringUTF16::StringUTF16(const CharUTF8* plainString, size_t length): MyBase()
{
	UTFConvert::FromUTF8ToUTF16(*this, StringUTF8(plainString, length));
}

StringUTF16& StringUTF16::operator+= (const StringUTF32& string)
{
	StringUTF16 string_UTF16;
	UTFConvert::FromUTF32ToUTF16(string_UTF16, string);	
	return *this += string_UTF16;
}

StringUTF16& StringUTF16::operator+= (const StringUTF16& string)
{
	MyBase::operator+= (string);
	return *this;
}

StringUTF16& StringUTF16::operator+= (const StringUTF8& string)
{
	StringUTF16 string_UTF16;
	UTFConvert::FromUTF8ToUTF16(string_UTF16, string);	
	return *this += string_UTF16;
}

StringUTF16& StringUTF16::operator+= (const CharUTF32* plainString)
{
	return *this += StringUTF32(plainString);
}

StringUTF16& StringUTF16::operator+= (const CharUTF16* plainString)
{
	return *this += StringUTF16(plainString);
}

StringUTF16& StringUTF16::operator+= (const CharUTF8* plainString)
{
	return *this += StringUTF8(plainString);
}

StringUTF16& StringUTF16::operator+= (CharUTF32 plainChar)
{
	return *this += StringUTF32(&plainChar, 1);
}

StringUTF16& StringUTF16::operator+= (CharUTF16 plainChar)
{
	return *this += StringUTF16(&plainChar, 1);
}

StringUTF16& StringUTF16::operator+= (CharUTF8 plainChar)
{
	return *this += StringUTF8(&plainChar, 1);
}

}

/* EOF */
