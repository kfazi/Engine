#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"
#include "CUTFConvert.hpp"

namespace Common
{

CStringUTF32::CStringUTF32(): CStringBase<TCharUTF32>()
{
}

CStringUTF32::CStringUTF32(unsigned int iCapacity): CStringBase<TCharUTF32>(iCapacity)
{
}

CStringUTF32::CStringUTF32(const CStringUTF32 &cStringUTF32): CStringBase<TCharUTF32>(cStringUTF32)
{
}

CStringUTF32::CStringUTF32(const CStringUTF16 &cStringUTF16): CStringBase<TCharUTF32>()
{
	CUTFConvert::FromUTF16ToUTF32(*this, cStringUTF16);	
}

CStringUTF32::CStringUTF32(const CStringUTF8 &cStringUTF8): CStringBase<TCharUTF32>()
{
	CUTFConvert::FromUTF8ToUTF32(*this, cStringUTF8);	
}

CStringUTF32::CStringUTF32(const TCharUTF32 *pString): CStringBase<TCharUTF32>(pString)
{
}

CStringUTF32::CStringUTF32(const TCharUTF16 *pString): CStringBase<TCharUTF32>()
{
	CUTFConvert::FromUTF16ToUTF32(*this, CStringUTF16(pString));	
}

CStringUTF32::CStringUTF32(const TCharUTF8 *pString): CStringBase<TCharUTF32>()
{
	CUTFConvert::FromUTF16ToUTF32(*this, CStringUTF8(pString));	
}

}

/* EOF */
