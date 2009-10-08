#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"
#include "CUTFConvert.hpp"

namespace Common
{

CStringUTF32::CStringUTF32(): MyType()
{
}

CStringUTF32::CStringUTF32(unsigned int iCapacity): MyType(iCapacity)
{
}

CStringUTF32::CStringUTF32(const CStringUTF32 &cStringUTF32): MyType(cStringUTF32)
{
}

CStringUTF32::CStringUTF32(const CStringUTF16 &cStringUTF16): MyType()
{
	CUTFConvert::FromUTF16ToUTF32(*this, cStringUTF16);	
}

CStringUTF32::CStringUTF32(const CStringUTF8 &cStringUTF8): MyType()
{
	CUTFConvert::FromUTF8ToUTF32(*this, cStringUTF8);	
}

CStringUTF32::CStringUTF32(const TCharUTF32 *pString): MyType(pString)
{
}

CStringUTF32::CStringUTF32(const TCharUTF32 *pString, unsigned int iLength): MyType(pString, iLength)
{
}

CStringUTF32::CStringUTF32(const TCharUTF16 *pString): MyType()
{
	CUTFConvert::FromUTF16ToUTF32(*this, CStringUTF16(pString));
}

CStringUTF32::CStringUTF32(const TCharUTF16 *pString, unsigned int iLength): MyType()
{
	CUTFConvert::FromUTF16ToUTF32(*this, CStringUTF16(pString, iLength));
}

CStringUTF32::CStringUTF32(const TCharUTF8 *pString): MyType()
{
	CUTFConvert::FromUTF8ToUTF32(*this, CStringUTF8(pString));	
}

CStringUTF32::CStringUTF32(const TCharUTF8 *pString, unsigned int iLength): MyType()
{
	CUTFConvert::FromUTF8ToUTF32(*this, CStringUTF8(pString, iLength));
}

CStringUTF32 &CStringUTF32::operator += (const CStringUTF32 &cString)
{
	static_cast<MyType>(*this) += static_cast<MyType>(cString);
	return *this;
}

CStringUTF32 &CStringUTF32::operator += (const CStringUTF16 &cString)
{
	CStringUTF32 cStringUTF32;
	CUTFConvert::FromUTF16ToUTF32(cStringUTF32, cString);	
	return *this += cStringUTF32;
}

CStringUTF32 &CStringUTF32::operator += (const CStringUTF8 &cString)
{
	CStringUTF32 cStringUTF32;
	CUTFConvert::FromUTF8ToUTF32(cStringUTF32, cString);	
	return *this += cStringUTF32;
}

CStringUTF32 &CStringUTF32::operator += (const TCharUTF32 *pString)
{
	return *this += CStringUTF32(pString);
}

CStringUTF32 &CStringUTF32::operator += (const TCharUTF16 *pString)
{
	return *this += CStringUTF16(pString);
}

CStringUTF32 &CStringUTF32::operator += (const TCharUTF8 *pString)
{
	return *this += CStringUTF8(pString);
}

CStringUTF32 &CStringUTF32::operator += (TCharUTF32 iChar)
{
	return *this += CStringUTF32(&iChar, 1);
}

CStringUTF32 &CStringUTF32::operator += (TCharUTF16 iChar)
{
	return *this += CStringUTF16(&iChar, 1);
}

CStringUTF32 &CStringUTF32::operator += (TCharUTF8 iChar)
{
	return *this += CStringUTF8(&iChar, 1);
}

}

/* EOF */
