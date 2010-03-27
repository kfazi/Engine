#include "StringUTF8.hpp"
#include "StringUTF16.hpp"
#include "StringUTF32.hpp"
#include "UTFConvert.hpp"

namespace Common
{

StringUTF32::StringUTF32(): MyBase()
{
}

StringUTF32::StringUTF32(size_t capacity): MyBase(capacity)
{
}

StringUTF32::StringUTF32(const StringUTF32& stringUTF32): MyBase(stringUTF32)
{
}

StringUTF32::StringUTF32(const StringUTF16& stringUTF16): MyBase()
{
	UTFConvert::FromUTF16ToUTF32(*this, stringUTF16);	
}

StringUTF32::StringUTF32(const StringUTF8& stringUTF8): MyBase()
{
	UTFConvert::FromUTF8ToUTF32(*this, stringUTF8);	
}

StringUTF32::StringUTF32(const CharUTF32* plainString): MyBase(plainString)
{
}

StringUTF32::StringUTF32(const CharUTF32* plainString, size_t length): MyBase(plainString, length)
{
}

StringUTF32::StringUTF32(const CharUTF16* plainString): MyBase()
{
	UTFConvert::FromUTF16ToUTF32(*this, StringUTF16(plainString));
}

StringUTF32::StringUTF32(const CharUTF16* plainString, size_t length): MyBase()
{
	UTFConvert::FromUTF16ToUTF32(*this, StringUTF16(plainString, length));
}

StringUTF32::StringUTF32(const CharUTF8* plainString): MyBase()
{
	UTFConvert::FromUTF8ToUTF32(*this, StringUTF8(plainString));	
}

StringUTF32::StringUTF32(const CharUTF8* plainString, size_t length): MyBase()
{
	UTFConvert::FromUTF8ToUTF32(*this, StringUTF8(plainString, length));
}

StringUTF32& StringUTF32::operator+= (const StringUTF32& string)
{
	//static_cast<MyBase>(*this) += static_cast<MyBase>(string);
	MyBase::operator+= (string);
	return *this;
}

StringUTF32& StringUTF32::operator+= (const StringUTF16& string)
{
	StringUTF32 string_UTF32;
	UTFConvert::FromUTF16ToUTF32(string_UTF32, string);	
	return *this += string_UTF32;
}

StringUTF32& StringUTF32::operator+= (const StringUTF8& string)
{
	StringUTF32 string_UTF32;
	UTFConvert::FromUTF8ToUTF32(string_UTF32, string);	
	return *this += string_UTF32;
}

StringUTF32& StringUTF32::operator+= (const CharUTF32* plainString)
{
	return *this += StringUTF32(plainString);
}

StringUTF32& StringUTF32::operator+= (const CharUTF16* plainString)
{
	return *this += StringUTF16(plainString);
}

StringUTF32& StringUTF32::operator+= (const CharUTF8* plainString)
{
	return *this += StringUTF8(plainString);
}

StringUTF32& StringUTF32::operator+= (CharUTF32 plainChar)
{
	return *this += StringUTF32(&plainChar, 1);
}

StringUTF32& StringUTF32::operator+= (CharUTF16 plainChar)
{
	return *this += StringUTF16(&plainChar, 1);
}

StringUTF32& StringUTF32::operator+= (CharUTF8 plainChar)
{
	return *this += StringUTF8(&plainChar, 1);
}

StringUTF32 StringUTF32::ToUpper() const
{
	/* TODO: UnicodeData.txt */
	StringUTF32 result(GetLength());
	for (ConstIterator iterator = Begin(); iterator != End(); ++iterator)
	{
		const CharacterData* character_data = GetCharacterData(*iterator);
		if (character_data != NULL)
			result += character_data->UppercaseMapping;
		else
			result += *iterator;
	}
	return result;
}

StringUTF32 StringUTF32::ToLower() const
{
	/* TODO: UnicodeData.txt (http://www.unicode.org/Public/5.2.0/) */
	StringUTF32 result(*this);
	return result;
}

}

/* EOF */
