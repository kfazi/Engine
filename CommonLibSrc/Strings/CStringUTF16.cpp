#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"
#include "CUTFConvert.hpp"

namespace Common
{

CStringUTF16::CStringUTF16(): CStringBase<TCharUTF16>()
{
}

CStringUTF16::CStringUTF16(unsigned int iCapacity): CStringBase<TCharUTF16>(iCapacity)
{
}

CStringUTF16::CStringUTF16(const CStringUTF32 &cStringUTF32): CStringBase<TCharUTF16>()
{
	CUTFConvert::FromUTF32ToUTF16(*this, cStringUTF32);	
}

CStringUTF16::CStringUTF16(const CStringUTF16 &cStringUTF16): CStringBase<TCharUTF16>(cStringUTF16)
{
}

CStringUTF16::CStringUTF16(const CStringUTF8 &cStringUTF8): CStringBase<TCharUTF16>()
{
	CUTFConvert::FromUTF8ToUTF16(*this, cStringUTF8);	
}

CStringUTF16::CStringUTF16(const TCharUTF32 *pString): CStringBase<TCharUTF16>()
{
	CUTFConvert::FromUTF32ToUTF16(*this, CStringUTF32(pString));
}

CStringUTF16::CStringUTF16(const TCharUTF16 *pString): CStringBase<TCharUTF16>(pString)
{
}

CStringUTF16::CStringUTF16(const TCharUTF8 *pString): CStringBase<TCharUTF16>()
{
	CUTFConvert::FromUTF8ToUTF16(*this, CStringUTF8(pString));	
}

}

/* EOF */
