#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"
#include "CUTFConvert.hpp"

namespace Common
{

CStringUTF16::CStringUTF16(): MyType()
{
}

CStringUTF16::CStringUTF16(unsigned int iCapacity): MyType(iCapacity)
{
}

CStringUTF16::CStringUTF16(const CStringUTF32 &cStringUTF32): MyType()
{
	CUTFConvert::FromUTF32ToUTF16(*this, cStringUTF32);	
}

CStringUTF16::CStringUTF16(const CStringUTF16 &cStringUTF16): MyType(cStringUTF16)
{
}

CStringUTF16::CStringUTF16(const CStringUTF8 &cStringUTF8): MyType()
{
	CUTFConvert::FromUTF8ToUTF16(*this, cStringUTF8);	
}

CStringUTF16::CStringUTF16(const TCharUTF32 *pString): MyType()
{
	CUTFConvert::FromUTF32ToUTF16(*this, CStringUTF32(pString));
}

CStringUTF16::CStringUTF16(const TCharUTF32 *pString, unsigned int iLength): MyType()
{
	CUTFConvert::FromUTF32ToUTF16(*this, CStringUTF32(pString, iLength));
}

CStringUTF16::CStringUTF16(const TCharUTF16 *pString): MyType(pString)
{
}

CStringUTF16::CStringUTF16(const TCharUTF16 *pString, unsigned int iLength): MyType(pString, iLength)
{
}

CStringUTF16::CStringUTF16(const TCharUTF8 *pString): MyType()
{
	CUTFConvert::FromUTF8ToUTF16(*this, CStringUTF8(pString));	
}

CStringUTF16::CStringUTF16(const TCharUTF8 *pString, unsigned int iLength): MyType()
{
	CUTFConvert::FromUTF8ToUTF16(*this, CStringUTF8(pString, iLength));
}

CStringUTF16 &CStringUTF16::operator += (const CStringUTF32 &cString)
{
	CStringUTF16 cStringUTF16;
	CUTFConvert::FromUTF32ToUTF16(cStringUTF16, cString);	
	return *this += cStringUTF16;
}

CStringUTF16 &CStringUTF16::operator += (const CStringUTF16 &cString)
{
	static_cast<MyType>(*this) += static_cast<MyType>(cString);
	return *this;
}

CStringUTF16 &CStringUTF16::operator += (const CStringUTF8 &cString)
{
	CStringUTF16 cStringUTF16;
	CUTFConvert::FromUTF8ToUTF16(cStringUTF16, cString);	
	return *this += cStringUTF16;
}

CStringUTF16 &CStringUTF16::operator += (const TCharUTF32 *pString)
{
	return *this += CStringUTF32(pString);
}

CStringUTF16 &CStringUTF16::operator += (const TCharUTF16 *pString)
{
	return *this += CStringUTF16(pString);
}

CStringUTF16 &CStringUTF16::operator += (const TCharUTF8 *pString)
{
	return *this += CStringUTF8(pString);
}

CStringUTF16 &CStringUTF16::operator += (TCharUTF32 iChar)
{
	return *this += CStringUTF32(&iChar, 1);
}

CStringUTF16 &CStringUTF16::operator += (TCharUTF16 iChar)
{
	return *this += CStringUTF16(&iChar, 1);
}

CStringUTF16 &CStringUTF16::operator += (TCharUTF8 iChar)
{
	return *this += CStringUTF8(&iChar, 1);
}

}

/* EOF */
