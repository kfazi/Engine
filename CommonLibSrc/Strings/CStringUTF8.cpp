#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"
#include "CUTFConvert.hpp"

namespace Common
{

CStringUTF8::CStringUTF8(): MyType()
{
}

CStringUTF8::CStringUTF8(unsigned int iCapacity): MyType(iCapacity)
{
}

CStringUTF8::CStringUTF8(const CStringUTF32& cStringUTF32): MyType()
{
	CUTFConvert::FromUTF32ToUTF8(*this, cStringUTF32);	
}

CStringUTF8::CStringUTF8(const CStringUTF16& cStringUTF16): MyType()
{
	CUTFConvert::FromUTF16ToUTF8(*this, cStringUTF16);
}

CStringUTF8::CStringUTF8(const CStringUTF8& cStringUTF8): MyType(cStringUTF8)
{
}

CStringUTF8::CStringUTF8(const TCharUTF32* pString): MyType()
{
	CUTFConvert::FromUTF32ToUTF8(*this, CStringUTF32(pString));
}

CStringUTF8::CStringUTF8(const TCharUTF32* pString, unsigned int iLength): MyType()
{
	CUTFConvert::FromUTF32ToUTF8(*this, CStringUTF32(pString, iLength));
}

CStringUTF8::CStringUTF8(const TCharUTF16* pString): MyType()
{
	CUTFConvert::FromUTF16ToUTF8(*this, CStringUTF16(pString));	
}

CStringUTF8::CStringUTF8(const TCharUTF16* pString, unsigned int iLength): MyType()
{
	CUTFConvert::FromUTF16ToUTF8(*this, CStringUTF16(pString, iLength));
}

CStringUTF8::CStringUTF8(const TCharUTF8* pString): MyType(pString)
{
}

CStringUTF8::CStringUTF8(const TCharUTF8* pString, unsigned int iLength): MyType(pString, iLength)
{
}

CStringUTF8& CStringUTF8::operator += (const CStringUTF32& cString)
{
	CStringUTF8 cStringUTF8;
	CUTFConvert::FromUTF32ToUTF8(cStringUTF8, cString);	
	return *this += cStringUTF8;
}

CStringUTF8& CStringUTF8::operator += (const CStringUTF16& cString)
{
	CStringUTF8 cStringUTF8;
	CUTFConvert::FromUTF16ToUTF8(cStringUTF8, cString);	
	return *this += cStringUTF8;
}

CStringUTF8& CStringUTF8::operator += (const CStringUTF8& cString)
{
	static_cast<MyType>(*this) += static_cast<MyType>(cString);
	return *this;
}

CStringUTF8& CStringUTF8::operator += (const TCharUTF32* pString)
{
	return *this += CStringUTF32(pString);
}

CStringUTF8& CStringUTF8::operator += (const TCharUTF16* pString)
{
	return *this += CStringUTF16(pString);
}

CStringUTF8& CStringUTF8::operator += (const TCharUTF8* pString)
{
	return *this += CStringUTF8(pString);
}

CStringUTF8& CStringUTF8::operator += (TCharUTF32 iChar)
{
	return *this += CStringUTF32(&iChar, 1);
}

CStringUTF8& CStringUTF8::operator += (TCharUTF16 iChar)
{
	return *this += CStringUTF16(&iChar, 1);
}

CStringUTF8& CStringUTF8::operator += (TCharUTF8 iChar)
{
	return *this += CStringUTF8(&iChar, 1);
}

}

/* EOF */
