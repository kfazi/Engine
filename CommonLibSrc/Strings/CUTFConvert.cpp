#include "CUTFConvert.hpp"
#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"

namespace Common
{

static const TCharUTF32 UNI_SUR_HIGH_START = 0xD800;
static const TCharUTF32 UNI_SUR_HIGH_END = 0xDBFF;
static const TCharUTF32 UNI_SUR_LOW_START = 0xDC00;
static const TCharUTF32 UNI_SUR_LOW_END = 0xDFFF;
static const TCharUTF32 UNI_MAX_BMP = 0x0000FFFF;
static const TCharUTF32 UNI_MAX_UTF16 = 0x0010FFFF;
static const TCharUTF32 UNI_MAX_UTF32 = 0x7FFFFFFF;
static const TCharUTF32 UNI_MAX_LEGAL_UTF32 = 0x0010FFFF;
static const TCharUTF32 halfBase = 0x0010000UL;
static const TCharUTF32 halfMask = 0x3FFUL;
static const int halfShift = 10; /* used for shifting by 10 bits */

static const char aTrailingBytesForUTF8[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};

static const unsigned int aOffsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL };

static const unsigned int aFirstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
static const TCharUTF32 byteMask = 0xBF;
static const TCharUTF32 byteMark = 0x80; 


CUTFConvert::CUTFConvert()
{
}

CUTFConvert::~CUTFConvert()
{
}

void CUTFConvert::FromUTF16ToUTF8(CStringUTF8 &cStringUTF8, const CStringUTF16 &cStringUTF16)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToWrite = 0;
	TCharUTF32 iChar;
	while (iSourceIndex < cStringUTF16.GetLength())
	{
		iChar = cStringUTF16[iSourceIndex++];
		if (iChar >= UNI_SUR_HIGH_START && iChar <= UNI_SUR_HIGH_END)
		{
			Assert(iSourceIndex < cStringUTF16.GetLength(), "Source exhausted");
			TCharUTF32 iChar2 = cStringUTF16[iSourceIndex++];
			Assert(iChar2 >= UNI_SUR_LOW_START && iChar2 <= UNI_SUR_LOW_END, "Illegal character");
			iChar = ((iChar - UNI_SUR_HIGH_START) << halfShift) + (iChar2 - UNI_SUR_LOW_START) + halfBase;
		}
		else
			Assert(iChar < UNI_SUR_LOW_START || iChar > UNI_SUR_LOW_END, "Illegal character");
		Assert(iChar < 0x110000, "Illegal character");
		if (iChar < 0x80)
			iBytesToWrite = 1;
		else if (iChar < 0x800)
			iBytesToWrite = 2;
		else if (iChar < 0x10000)
			iBytesToWrite = 3;
		else if (iChar < 0x110000)
			iBytesToWrite = 4;
		cStringUTF8 += static_cast<TCharUTF8>((iChar >> 18)| aFirstByteMark[iBytesToWrite]);
		if (iBytesToWrite > 1)
		{
			cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 12) | aFirstByteMark[iBytesToWrite]) & byteMask);
			if (iBytesToWrite > 2)
			{
				cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 6) | aFirstByteMark[iBytesToWrite]) & byteMask);
				if (iBytesToWrite > 3)
					cStringUTF8 += static_cast<TCharUTF8>((iChar | aFirstByteMark[iBytesToWrite]) & byteMask);
			}
		}
	}
}

void CUTFConvert::FromUTF32ToUTF8(CStringUTF8 &cStringUTF8, const CStringUTF32 &cStringUTF32)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToWrite = 0;
	TCharUTF32 iChar;
	while (iSourceIndex < cStringUTF32.GetLength())
	{
		iChar = cStringUTF32[iSourceIndex++];
		Assert(iChar < UNI_SUR_HIGH_START || iChar > UNI_SUR_LOW_END, "Illegal character");
		Assert(iChar <= UNI_MAX_LEGAL_UTF32, "Illegal character");
		if (iChar < 0x80)
			iBytesToWrite = 1;
		else if (iChar < 0x800)
			iBytesToWrite = 2;
		else if (iChar < 0x10000)
			iBytesToWrite = 3;
		else
			iBytesToWrite = 4;
		cStringUTF8 += static_cast<TCharUTF8>((iChar >> 18)| aFirstByteMark[iBytesToWrite]);
		if (iBytesToWrite > 1)
		{
			cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 12) | aFirstByteMark[iBytesToWrite]) & byteMask);
			if (iBytesToWrite > 2)
			{
				cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 6) | aFirstByteMark[iBytesToWrite]) & byteMask);
				if (iBytesToWrite > 3)
					cStringUTF8 += static_cast<TCharUTF8>((iChar | aFirstByteMark[iBytesToWrite]) & byteMask);
			}
		}
	}
}

void CUTFConvert::FromUTF8ToUTF16(CStringUTF16 &cStringUTF16, const CStringUTF8 &cStringUTF8)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToRead = 0;
	TCharUTF32 iChar;
	while (iSourceIndex < cStringUTF8.GetLength())
	{
		iBytesToRead = aTrailingBytesForUTF8[cStringUTF8[iSourceIndex]];
		Assert(iSourceIndex + iBytesToRead < cStringUTF8.GetLength(), "Source exhausted");
		Assert(IsLegalUTF8(), "Illegal UTF-8");
		switch (iBytesToRead)
		{
			case 5: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 4: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 3: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 2: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 1: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 0: iChar += cStringUTF8[iSourceIndex++];
		}
		iChar -= aOffsetsFromUTF8[iBytesToRead];
		Assert(iChar <= UNI_MAX_UTF16, "Illegal character");
		if (iChar <= UNI_MAX_BMP)
		{
			Assert(iChar < UNI_SUR_HIGH_START || iChar > UNI_SUR_LOW_END, "Illegal character");
			cStringUTF16 += static_cast<TCharUTF16>(iChar);
		}
		else
		{
			iChar -= halfBase;
			cStringUTF16 += static_cast<TCharUTF16>((iChar >> halfShift) + UNI_SUR_HIGH_START);
			cStringUTF16 += static_cast<TCharUTF16>((iChar & halfMask) + UNI_SUR_LOW_START);
		}
	}
}

void CUTFConvert::FromUTF32ToUTF16(CStringUTF16 &cStringUTF16, const CStringUTF32 &cStringUTF32)
{
	unsigned int iSourceIndex = 0;
	TCharUTF32 iChar;
	while (iSourceIndex < cStringUTF32.GetLength())
	{
		iChar = cStringUTF32[iSourceIndex++];
		Assert(iChar <= UNI_MAX_LEGAL_UTF32, "Illegal character");
		if (iChar <= UNI_MAX_BMP)
		{
			Assert(iChar < UNI_SUR_HIGH_START || iChar > UNI_SUR_LOW_END, "Illegal character");
			cStringUTF16 += static_cast<TCharUTF16>(iChar);
		}
		else
		{
			iChar -= halfBase;
			cStringUTF16 += static_cast<TCharUTF16>((iChar >> halfShift) + UNI_SUR_HIGH_START);
			cStringUTF16 += static_cast<TCharUTF16>((iChar & halfMask) + UNI_SUR_LOW_START);
		}
	}
}

void CUTFConvert::FromUTF8ToUTF32(CStringUTF32 &cStringUTF32, const CStringUTF8 &cStringUTF8)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToRead = 0;
	TCharUTF32 iChar;
	while (iSourceIndex < cStringUTF8.GetLength())
	{
		iBytesToRead = aTrailingBytesForUTF8[cStringUTF8[iSourceIndex]];
		Assert(iSourceIndex + iBytesToRead < cStringUTF8.GetLength(), "Source exhausted");
		Assert(IsLegalUTF8(), "Illegal UTF-8");
		switch (iBytesToRead)
		{
			case 5: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 4: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 3: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 2: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 1: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 0: iChar += cStringUTF8[iSourceIndex++];
		}
		iChar -= aOffsetsFromUTF8[iBytesToRead];
		Assert(iChar <= UNI_MAX_LEGAL_UTF32, "Illegal character");
		Assert(iChar < UNI_SUR_HIGH_START || iChar > UNI_SUR_LOW_END, "Illegal character");
		cStringUTF32 += iChar;
	}
}

void CUTFConvert::FromUTF16ToUTF32(CStringUTF32 &cStringUTF32, const CStringUTF16 &cStringUTF16)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToWrite = 0;
	TCharUTF32 iChar;
	while (iSourceIndex < cStringUTF16.GetLength())
	{
		iChar = cStringUTF16[iSourceIndex++];
		if (iChar >= UNI_SUR_HIGH_START && iChar <= UNI_SUR_HIGH_END)
		{
			Assert(iSourceIndex < cStringUTF16.GetLength(), "Source exhausted");
			TCharUTF32 iChar2 = cStringUTF16[iSourceIndex++];
			Assert(iChar2 >= UNI_SUR_LOW_START && iChar2 <= UNI_SUR_LOW_END, "Illegal character");
			iChar = ((iChar - UNI_SUR_HIGH_START) << halfShift) + (iChar2 - UNI_SUR_LOW_START) + halfBase;
		}
		else
			Assert(iChar < UNI_SUR_LOW_START || iChar > UNI_SUR_LOW_END, "Illegal character");
		Assert(iChar < 0x110000, "Illegal character");
		cStringUTF32 += iChar;
	}
}

}

/* EOF */
