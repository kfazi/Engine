#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"
#include "CUTFConvert.hpp"

namespace Common
{

CStringUTF8::CStringUTF8(): CStringBase<TCharUTF8>()
{
}

CStringUTF8::CStringUTF8(unsigned int iCapacity): CStringBase<TCharUTF8>(iCapacity)
{
}

CStringUTF8::CStringUTF8(const CStringUTF32 &cStringUTF32): CStringBase<TCharUTF8>()
{
	CUTFConvert::FromUTF32ToUTF8(*this, cStringUTF32);	
}

CStringUTF8::CStringUTF8(const CStringUTF16 &cStringUTF16): CStringBase<TCharUTF8>()
{
	CUTFConvert::FromUTF16ToUTF8(*this, cStringUTF16);
}

CStringUTF8::CStringUTF8(const CStringUTF8 &cStringUTF8): CStringBase<TCharUTF8>(cStringUTF8)
{
}

CStringUTF8::CStringUTF8(const TCharUTF32 *pString): CStringBase<TCharUTF8>()
{
	CUTFConvert::FromUTF32ToUTF8(*this, CStringUTF32(pString));
}

CStringUTF8::CStringUTF8(const TCharUTF16 *pString): CStringBase<TCharUTF8>()
{
	CUTFConvert::FromUTF16ToUTF8(*this, CStringUTF16(pString));	
}

CStringUTF8::CStringUTF8(const TCharUTF8 *pString): CStringBase<TCharUTF8>(pString)
{
}

}

/* EOF */
