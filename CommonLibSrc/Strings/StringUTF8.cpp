#include "StringUTF8.hpp"
#include "StringUTF16.hpp"
#include "StringUTF32.hpp"
#include "UTFConvert.hpp"

namespace Common
{

StringUTF8::StringUTF8() : MyBase()
{
}

StringUTF8::StringUTF8(size_t capacity): MyBase(capacity)
{
}

StringUTF8::StringUTF8(const StringUTF32& stringUTF32): MyBase()
{
	UTFConvert::FromUTF32ToUTF8(*this, stringUTF32);	
}

StringUTF8::StringUTF8(const StringUTF16& stringUTF16): MyBase()
{
	UTFConvert::FromUTF16ToUTF8(*this, stringUTF16);
}

StringUTF8::StringUTF8(const StringUTF8& stringUTF8): MyBase(stringUTF8)
{
}

StringUTF8::StringUTF8(const CharUTF32* plainString): MyBase()
{
	UTFConvert::FromUTF32ToUTF8(*this, StringUTF32(plainString));
}

StringUTF8::StringUTF8(const CharUTF32* plainString, size_t length): MyBase()
{
	UTFConvert::FromUTF32ToUTF8(*this, StringUTF32(plainString, length));
}

StringUTF8::StringUTF8(const CharUTF16* plainString): MyBase()
{
	UTFConvert::FromUTF16ToUTF8(*this, StringUTF16(plainString));	
}

StringUTF8::StringUTF8(const CharUTF16* plainString, size_t length): MyBase()
{
	UTFConvert::FromUTF16ToUTF8(*this, StringUTF16(plainString, length));
}

StringUTF8::StringUTF8(const CharUTF8* plainString): MyBase(plainString)
{
}

StringUTF8::StringUTF8(const CharUTF8* plainString, size_t length): MyBase(plainString, length)
{
}

StringUTF8& StringUTF8::operator+= (const StringUTF32& string)
{
	StringUTF8 string_UTF8;
	UTFConvert::FromUTF32ToUTF8(string_UTF8, string);	
	return *this += string_UTF8;
}

StringUTF8& StringUTF8::operator+= (const StringUTF16& string)
{
	StringUTF8 string_UTF8;
	UTFConvert::FromUTF16ToUTF8(string_UTF8, string);	
	return *this += string_UTF8;
}

StringUTF8& StringUTF8::operator+= (const StringUTF8& string)
{
	MyBase::operator+= (string);
	return *this;
}

StringUTF8& StringUTF8::operator+= (const CharUTF32* plainString)
{
	return *this += StringUTF32(plainString);
}

StringUTF8& StringUTF8::operator+= (const CharUTF16* plainString)
{
	return *this += StringUTF16(plainString);
}

StringUTF8& StringUTF8::operator+= (const CharUTF8* plainString)
{
	return *this += StringUTF8(plainString);
}

StringUTF8& StringUTF8::operator+= (CharUTF32 plainChar)
{
	return *this += StringUTF32(&plainChar, 1);
}

StringUTF8& StringUTF8::operator+= (CharUTF16 plainChar)
{
	return *this += StringUTF16(&plainChar, 1);
}

StringUTF8& StringUTF8::operator+= (CharUTF8 plainChar)
{
	return *this += StringUTF8(&plainChar, 1);
}

}

/* EOF */
