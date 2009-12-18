#include "CUTFConvert.hpp"
#include "CStringUTF8.hpp"
#include "CStringUTF16.hpp"
#include "CStringUTF32.hpp"

namespace Common
{

static const TCharUTF32 g_iUnicodeSurrogateHighStart = 0xD800UL;
static const TCharUTF32 g_iUnicodeSurrogateHighEnd = 0xDBFFUL;
static const TCharUTF32 g_iUnicodeSurrogateLowStart = 0xDC00UL;
static const TCharUTF32 g_iUnicodeSurrogateLowEnd = 0xDFFFUL;
static const TCharUTF32 g_iUnicodeMaxBasicMultilingualPlane = 0x0000FFFFUL;
static const TCharUTF32 g_iUnicodeMaxUTF16 = 0x0010FFFFUL;
static const TCharUTF32 g_iUnicodeMaxUTF32 = 0x7FFFFFFFUL;
static const TCharUTF32 g_iUnicodeMaxLegalUTF32 = 0x0010FFFFUL;
static const TCharUTF32 g_iHalfBase = 0x0010000UL;
static const TCharUTF32 g_iHalfMask = 0x3FFUL;
static const TCharUTF32 g_iByteMask = 0xBFUL;
static const TCharUTF32 g_iByteMark = 0x80UL; 
static const int g_iHalfShift = 10;

static const int g_aTrailingBytesForUTF8[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};

static const unsigned int g_aOffsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL };

static const unsigned int g_aFirstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };


CUTFConvert::CUTFConvert()
{
}

CUTFConvert::~CUTFConvert()
{
}

bool CUTFConvert::IsLegalUTF8(const CStringUTF8& cStringUTF8, unsigned int iIndex, unsigned int iBytesToRead)
{
	TCharUTF8 iChar;
	switch (iBytesToRead)
	{
		default:
			return false;
		case 4:
			if ((iChar = cStringUTF8[iIndex + (--iBytesToRead) - 1]) < 0x80 || iChar > 0xBF)
				return false;
		case 3:
			if ((iChar = cStringUTF8[iIndex + (--iBytesToRead) - 1]) < 0x80 || iChar > 0xBF)
				return false;
		case 2:
			if ((iChar = cStringUTF8[iIndex + (--iBytesToRead) - 1]) > 0xBF)
				return false;
			switch (cStringUTF8[iIndex])
			{
				case 0xE0:
					if (iChar < 0xA0)
						return false;
					break;
				case 0xED:
					if (iChar > 0x9F)
						return false;
					break;
				case 0xF0:
					if (iChar < 0x90)
						return false;
					break;
				case 0xF4:
					if (iChar > 0x8F)
						return false;
					break;
				default:
					if (iChar < 0x80)
						return false;
			}
		case 1:
			if (cStringUTF8[iIndex] >= 0x80 && cStringUTF8[iIndex] < 0xC2)
				return false;
	}
	if (cStringUTF8[iIndex] > 0xF4)
		return false;
	return true;
}

void CUTFConvert::FromUTF16ToUTF8(CStringUTF8& cStringUTF8, const CStringUTF16& cStringUTF16)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToWrite = 0;
	TCharUTF32 iChar;
	cStringUTF8.Allocate(cStringUTF8.GetLength() + cStringUTF16.GetLength());
	while (iSourceIndex < cStringUTF16.GetLength())
	{
		iChar = cStringUTF16[iSourceIndex++];
		if (iChar >= g_iUnicodeSurrogateHighStart && iChar <= g_iUnicodeSurrogateHighEnd)
		{
			Assert(iSourceIndex < cStringUTF16.GetLength(), "Source exhausted");
			TCharUTF32 iChar2 = cStringUTF16[iSourceIndex++];
			Assert(iChar2 >= g_iUnicodeSurrogateLowStart && iChar2 <= g_iUnicodeSurrogateLowEnd, "Illegal character");
			iChar = ((iChar - g_iUnicodeSurrogateHighStart) << g_iHalfShift) + (iChar2 - g_iUnicodeSurrogateLowStart) + g_iHalfBase;
		}
		else
			Assert(iChar < g_iUnicodeSurrogateLowStart || iChar > g_iUnicodeSurrogateLowEnd, "Illegal character");
		Assert(iChar < 0x110000, "Illegal character");
		if (iChar < 0x80)
			iBytesToWrite = 1;
		else if (iChar < 0x800)
			iBytesToWrite = 2;
		else if (iChar < 0x10000)
			iBytesToWrite = 3;
		else if (iChar < 0x110000)
			iBytesToWrite = 4;
		cStringUTF8 += static_cast<TCharUTF8>((iChar >> 18)| g_aFirstByteMark[iBytesToWrite]);
		if (iBytesToWrite > 1)
		{
			cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 12) | g_aFirstByteMark[iBytesToWrite]) & g_iByteMask);
			if (iBytesToWrite > 2)
			{
				cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 6) | g_aFirstByteMark[iBytesToWrite]) & g_iByteMask);
				if (iBytesToWrite > 3)
					cStringUTF8 += static_cast<TCharUTF8>((iChar | g_aFirstByteMark[iBytesToWrite]) & g_iByteMask);
			}
		}
	}
}

void CUTFConvert::FromUTF32ToUTF8(CStringUTF8& cStringUTF8, const CStringUTF32& cStringUTF32)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToWrite = 0;
	TCharUTF32 iChar;
	cStringUTF8.Allocate(cStringUTF8.GetLength() + cStringUTF32.GetLength());
	while (iSourceIndex < cStringUTF32.GetLength())
	{
		iChar = cStringUTF32[iSourceIndex++];
		Assert(iChar < g_iUnicodeSurrogateHighStart || iChar > g_iUnicodeSurrogateLowEnd, "Illegal character");
		Assert(iChar <= g_iUnicodeMaxLegalUTF32, "Illegal character");
		if (iChar < 0x80)
			iBytesToWrite = 1;
		else if (iChar < 0x800)
			iBytesToWrite = 2;
		else if (iChar < 0x10000)
			iBytesToWrite = 3;
		else
			iBytesToWrite = 4;
		cStringUTF8 += static_cast<TCharUTF8>((iChar >> 18)| g_aFirstByteMark[iBytesToWrite]);
		if (iBytesToWrite > 1)
		{
			cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 12) | g_aFirstByteMark[iBytesToWrite]) & g_iByteMask);
			if (iBytesToWrite > 2)
			{
				cStringUTF8 += static_cast<TCharUTF8>(((iChar >> 6) | g_aFirstByteMark[iBytesToWrite]) & g_iByteMask);
				if (iBytesToWrite > 3)
					cStringUTF8 += static_cast<TCharUTF8>((iChar | g_aFirstByteMark[iBytesToWrite]) & g_iByteMask);
			}
		}
	}
}

void CUTFConvert::FromUTF8ToUTF16(CStringUTF16& cStringUTF16, const CStringUTF8& cStringUTF8)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToRead = 0;
	TCharUTF32 iChar = 0;
	cStringUTF16.Allocate(cStringUTF16.GetLength() + cStringUTF8.GetLength());
	while (iSourceIndex < cStringUTF8.GetLength())
	{
		iBytesToRead = g_aTrailingBytesForUTF8[cStringUTF8[iSourceIndex]];
		Assert(iSourceIndex + iBytesToRead < cStringUTF8.GetLength(), "Source exhausted");
		Assert(IsLegalUTF8(cStringUTF8, iSourceIndex, iBytesToRead + 1), "Illegal UTF-8");
		switch (iBytesToRead)
		{
			case 5: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 4: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 3: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 2: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 1: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 0: iChar += cStringUTF8[iSourceIndex++];
		}
		iChar -= g_aOffsetsFromUTF8[iBytesToRead];
		Assert(iChar <= g_iUnicodeMaxUTF16, "Illegal character");
		if (iChar <= g_iUnicodeMaxBasicMultilingualPlane)
		{
			Assert(iChar < g_iUnicodeSurrogateHighStart || iChar > g_iUnicodeSurrogateLowEnd, "Illegal character");
			cStringUTF16 += static_cast<TCharUTF16>(iChar);
		}
		else
		{
			iChar -= g_iHalfBase;
			cStringUTF16 += static_cast<TCharUTF16>((iChar >> g_iHalfShift) + g_iUnicodeSurrogateHighStart);
			cStringUTF16 += static_cast<TCharUTF16>((iChar & g_iHalfMask) + g_iUnicodeSurrogateLowStart);
		}
	}
}

void CUTFConvert::FromUTF32ToUTF16(CStringUTF16& cStringUTF16, const CStringUTF32& cStringUTF32)
{
	unsigned int iSourceIndex = 0;
	TCharUTF32 iChar;
	cStringUTF16.Allocate(cStringUTF16.GetLength() + cStringUTF32.GetLength());
	while (iSourceIndex < cStringUTF32.GetLength())
	{
		iChar = cStringUTF32[iSourceIndex++];
		Assert(iChar <= g_iUnicodeMaxLegalUTF32, "Illegal character");
		if (iChar <= g_iUnicodeMaxBasicMultilingualPlane)
		{
			Assert(iChar < g_iUnicodeSurrogateHighStart || iChar > g_iUnicodeSurrogateLowEnd, "Illegal character");
			cStringUTF16 += static_cast<TCharUTF16>(iChar);
		}
		else
		{
			iChar -= g_iHalfBase;
			cStringUTF16 += static_cast<TCharUTF16>((iChar >> g_iHalfShift) + g_iUnicodeSurrogateHighStart);
			cStringUTF16 += static_cast<TCharUTF16>((iChar & g_iHalfMask) + g_iUnicodeSurrogateLowStart);
		}
	}
}

void CUTFConvert::FromUTF8ToUTF32(CStringUTF32& cStringUTF32, const CStringUTF8& cStringUTF8)
{
	unsigned int iSourceIndex = 0;
	unsigned int iBytesToRead = 0;
	TCharUTF32 iChar = 0;
	cStringUTF32.Allocate(cStringUTF32.GetLength() + cStringUTF8.GetLength());
	while (iSourceIndex < cStringUTF8.GetLength())
	{
		iBytesToRead = g_aTrailingBytesForUTF8[cStringUTF8[iSourceIndex]];
		Assert(iSourceIndex + iBytesToRead < cStringUTF8.GetLength(), "Source exhausted");
		Assert(IsLegalUTF8(cStringUTF8, iSourceIndex, iBytesToRead + 1), "Illegal UTF-8");
		switch (iBytesToRead)
		{
			case 5: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 4: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6; /* Illegal UTF-8. */
			case 3: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 2: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 1: iChar += cStringUTF8[iSourceIndex++]; iChar <<= 6;
			case 0: iChar += cStringUTF8[iSourceIndex++];
		}
		iChar -= g_aOffsetsFromUTF8[iBytesToRead];
		Assert(iChar <= g_iUnicodeMaxLegalUTF32, "Illegal character");
		Assert(iChar < g_iUnicodeSurrogateHighStart || iChar > g_iUnicodeSurrogateLowEnd, "Illegal character");
		cStringUTF32 += iChar;
	}
}

void CUTFConvert::FromUTF16ToUTF32(CStringUTF32& cStringUTF32, const CStringUTF16& cStringUTF16)
{
	unsigned int iSourceIndex = 0;
//	unsigned int iBytesToWrite = 0;
	TCharUTF32 iChar;
	cStringUTF32.Allocate(cStringUTF32.GetLength() + cStringUTF16.GetLength());
	while (iSourceIndex < cStringUTF16.GetLength())
	{
		iChar = cStringUTF16[iSourceIndex++];
		if (iChar >= g_iUnicodeSurrogateHighStart && iChar <= g_iUnicodeSurrogateHighEnd)
		{
			Assert(iSourceIndex < cStringUTF16.GetLength(), "Source exhausted");
			TCharUTF32 iChar2 = cStringUTF16[iSourceIndex++];
			Assert(iChar2 >= g_iUnicodeSurrogateLowStart && iChar2 <= g_iUnicodeSurrogateLowEnd, "Illegal character");
			iChar = ((iChar - g_iUnicodeSurrogateHighStart) << g_iHalfShift) + (iChar2 - g_iUnicodeSurrogateLowStart) + g_iHalfBase;
		}
		else
			Assert(iChar < g_iUnicodeSurrogateLowStart || iChar > g_iUnicodeSurrogateLowEnd, "Illegal character");
		Assert(iChar < 0x110000, "Illegal character");
		cStringUTF32 += iChar;
	}
}

}

/* EOF */
