#include "UTFConvert.hpp"
#include "StringUTF8.hpp"
#include "StringUTF16.hpp"
#include "StringUTF32.hpp"

namespace Common
{

static const CharUTF32 gUnicodeSurrogateHighStart = 0xD800UL;
static const CharUTF32 gUnicodeSurrogateHighEnd = 0xDBFFUL;
static const CharUTF32 gUnicodeSurrogateLowStart = 0xDC00UL;
static const CharUTF32 gUnicodeSurrogateLowEnd = 0xDFFFUL;
static const CharUTF32 gUnicodeMaxBasicMultilingualPlane = 0x0000FFFFUL;
static const CharUTF32 gUnicodeMaxUTF16 = 0x0010FFFFUL;
static const CharUTF32 gUnicodeMaxUTF32 = 0x7FFFFFFFUL;
static const CharUTF32 gUnicodeMaxLegalUTF32 = 0x0010FFFFUL;
static const CharUTF32 gHalfBase = 0x0010000UL;
static const CharUTF32 gHalfMask = 0x3FFUL;
static const CharUTF32 gByteMask = 0xBFUL;
static const CharUTF32 gByteMark = 0x80UL; 
static const int gHalfShift = 10;

static const int gTrailingBytesForUTF8[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};

static const unsigned int gOffsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
	0x03C82080UL, 0xFA082080UL, 0x82082080UL };

static const unsigned int gFirstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };


UTFConvert::UTFConvert()
{
}

UTFConvert::~UTFConvert()
{
}

bool UTFConvert::IsLegalUTF8(const StringUTF8& stringUTF8, size_t index, int bytesToRead)
{
	CharUTF8 current_char;
	switch (bytesToRead)
	{
		default:
			return false;
		case 4:
			if ((current_char = stringUTF8[index + (--bytesToRead) - 1]) < 0x80 || current_char > 0xBF)
				return false;
		case 3:
			if ((current_char = stringUTF8[index + (--bytesToRead) - 1]) < 0x80 || current_char > 0xBF)
				return false;
		case 2:
			if ((current_char = stringUTF8[index + (--bytesToRead) - 1]) > 0xBF)
				return false;
			switch (stringUTF8[index])
			{
				case 0xE0:
					if (current_char < 0xA0)
						return false;
					break;
				case 0xED:
					if (current_char > 0x9F)
						return false;
					break;
				case 0xF0:
					if (current_char < 0x90)
						return false;
					break;
				case 0xF4:
					if (current_char > 0x8F)
						return false;
					break;
				default:
					if (current_char < 0x80)
						return false;
			}
		case 1:
			if (stringUTF8[index] >= 0x80 && stringUTF8[index] < 0xC2)
				return false;
	}
	if (stringUTF8[index] > 0xF4)
		return false;
	return true;
}

void UTFConvert::FromUTF16ToUTF8(StringUTF8& stringUTF8, const StringUTF16& stringUTF16)
{
	unsigned int source_index = 0;
	unsigned int bytes_to_write = 0;
	CharUTF32 current_char;
	stringUTF8.Allocate(stringUTF8.GetLength() + stringUTF16.GetLength());
	while (source_index < stringUTF16.GetLength())
	{
		current_char = stringUTF16[source_index++];
		if (current_char >= gUnicodeSurrogateHighStart && current_char <= gUnicodeSurrogateHighEnd)
		{
			Assert(source_index < stringUTF16.GetLength(), "Source exhausted");
			CharUTF32 iChar2 = stringUTF16[source_index++];
			Assert(iChar2 >= gUnicodeSurrogateLowStart && iChar2 <= gUnicodeSurrogateLowEnd,
				"Illegal character");
			current_char = ((current_char - gUnicodeSurrogateHighStart) << gHalfShift) + (iChar2 -
				gUnicodeSurrogateLowStart) + gHalfBase;
		}
		else
			Assert(current_char < gUnicodeSurrogateLowStart || current_char > gUnicodeSurrogateLowEnd,
				"Illegal character");
		Assert(current_char < 0x110000, "Illegal character");
		if (current_char < 0x80)
			bytes_to_write = 1;
		else if (current_char < 0x800)
			bytes_to_write = 2;
		else if (current_char < 0x10000)
			bytes_to_write = 3;
		else if (current_char < 0x110000)
			bytes_to_write = 4;
		stringUTF8 += static_cast<CharUTF8>((current_char >> 18)| gFirstByteMark[bytes_to_write]);
		if (bytes_to_write > 1)
		{
			stringUTF8 += static_cast<CharUTF8>(((current_char >> 12) | gFirstByteMark[bytes_to_write]) &
				gByteMask);
			if (bytes_to_write > 2)
			{
				stringUTF8 += static_cast<CharUTF8>(((current_char >> 6) | gFirstByteMark[bytes_to_write]) &
					gByteMask);
				if (bytes_to_write > 3)
					stringUTF8 += static_cast<CharUTF8>((current_char | gFirstByteMark[bytes_to_write]) &
						gByteMask);
			}
		}
	}
}

void UTFConvert::FromUTF32ToUTF8(StringUTF8& stringUTF8, const StringUTF32& stringUTF32)
{
	unsigned int source_index = 0;
	unsigned int bytes_to_write = 0;
	CharUTF32 current_char;
	stringUTF8.Allocate(stringUTF8.GetLength() + stringUTF32.GetLength());
	while (source_index < stringUTF32.GetLength())
	{
		current_char = stringUTF32[source_index++];
		Assert(current_char < gUnicodeSurrogateHighStart || current_char > gUnicodeSurrogateLowEnd,
			"Illegal character");
		Assert(current_char <= gUnicodeMaxLegalUTF32, "Illegal character");
		if (current_char < 0x80)
			bytes_to_write = 1;
		else if (current_char < 0x800)
			bytes_to_write = 2;
		else if (current_char < 0x10000)
			bytes_to_write = 3;
		else
			bytes_to_write = 4;
		stringUTF8 += static_cast<CharUTF8>((current_char >> 18)| gFirstByteMark[bytes_to_write]);
		if (bytes_to_write > 1)
		{
			stringUTF8 += static_cast<CharUTF8>(((current_char >> 12) | gFirstByteMark[bytes_to_write]) &
				gByteMask);
			if (bytes_to_write > 2)
			{
				stringUTF8 += static_cast<CharUTF8>(((current_char >> 6) | gFirstByteMark[bytes_to_write]) &
					gByteMask);
				if (bytes_to_write > 3)
					stringUTF8 += static_cast<CharUTF8>((current_char | gFirstByteMark[bytes_to_write]) &
						gByteMask);
			}
		}
	}
}

void UTFConvert::FromUTF8ToUTF16(StringUTF16& stringUTF16, const StringUTF8& stringUTF8)
{
	unsigned int source_index = 0;
	unsigned int bytes_to_read = 0;
	CharUTF32 current_char;
	stringUTF16.Allocate(stringUTF16.GetLength() + stringUTF8.GetLength());
	while (source_index < stringUTF8.GetLength())
	{
		current_char = 0;
		bytes_to_read = gTrailingBytesForUTF8[stringUTF8[source_index]];
		Assert(source_index + bytes_to_read < stringUTF8.GetLength(), "Source exhausted");
		Assert(IsLegalUTF8(stringUTF8, source_index, bytes_to_read + 1), "Illegal UTF-8");
		switch (bytes_to_read)
		{
			case 5: current_char += stringUTF8[source_index++]; current_char <<= 6; /* Illegal UTF-8. */
			case 4: current_char += stringUTF8[source_index++]; current_char <<= 6; /* Illegal UTF-8. */
			case 3: current_char += stringUTF8[source_index++]; current_char <<= 6;
			case 2: current_char += stringUTF8[source_index++]; current_char <<= 6;
			case 1: current_char += stringUTF8[source_index++]; current_char <<= 6;
			case 0: current_char += stringUTF8[source_index++];
		}
		current_char -= gOffsetsFromUTF8[bytes_to_read];
		Assert(current_char <= gUnicodeMaxUTF16, "Illegal character");
		if (current_char <= gUnicodeMaxBasicMultilingualPlane)
		{
			Assert(current_char < gUnicodeSurrogateHighStart || current_char > gUnicodeSurrogateLowEnd,
				"Illegal character");
			stringUTF16 += static_cast<CharUTF16>(current_char);
		}
		else
		{
			current_char -= gHalfBase;
			stringUTF16 += static_cast<CharUTF16>((current_char >> gHalfShift) +
				gUnicodeSurrogateHighStart);
			stringUTF16 += static_cast<CharUTF16>((current_char & gHalfMask) + gUnicodeSurrogateLowStart);
		}
	}
}

void UTFConvert::FromUTF32ToUTF16(StringUTF16& stringUTF16, const StringUTF32& stringUTF32)
{
	unsigned int source_index = 0;
	CharUTF32 current_char;
	stringUTF16.Allocate(stringUTF16.GetLength() + stringUTF32.GetLength());
	while (source_index < stringUTF32.GetLength())
	{
		current_char = stringUTF32[source_index++];
		Assert(current_char <= gUnicodeMaxLegalUTF32, "Illegal character");
		if (current_char <= gUnicodeMaxBasicMultilingualPlane)
		{
			Assert(current_char < gUnicodeSurrogateHighStart || current_char > gUnicodeSurrogateLowEnd,
				"Illegal character");
			stringUTF16 += static_cast<CharUTF16>(current_char);
		}
		else
		{
			current_char -= gHalfBase;
			stringUTF16 += static_cast<CharUTF16>((current_char >> gHalfShift) +
				gUnicodeSurrogateHighStart);
			stringUTF16 += static_cast<CharUTF16>((current_char & gHalfMask) + gUnicodeSurrogateLowStart);
		}
	}
}

void UTFConvert::FromUTF8ToUTF32(StringUTF32& stringUTF32, const StringUTF8& stringUTF8)
{
	unsigned int source_index = 0;
	unsigned int bytes_to_read = 0;
	CharUTF32 current_char;
	stringUTF32.Allocate(stringUTF32.GetLength() + stringUTF8.GetLength());
	while (source_index < stringUTF8.GetLength())
	{
		current_char = 0;
		bytes_to_read = gTrailingBytesForUTF8[stringUTF8[source_index]];
		Assert(source_index + bytes_to_read < stringUTF8.GetLength(), "Source exhausted");
		Assert(IsLegalUTF8(stringUTF8, source_index, bytes_to_read + 1), "Illegal UTF-8");
		switch (bytes_to_read)
		{
			case 5: current_char += stringUTF8[source_index++]; current_char <<= 6; /* Illegal UTF-8. */
			case 4: current_char += stringUTF8[source_index++]; current_char <<= 6; /* Illegal UTF-8. */
			case 3: current_char += stringUTF8[source_index++]; current_char <<= 6;
			case 2: current_char += stringUTF8[source_index++]; current_char <<= 6;
			case 1: current_char += stringUTF8[source_index++]; current_char <<= 6;
			case 0: current_char += stringUTF8[source_index++];
		}
		current_char -= gOffsetsFromUTF8[bytes_to_read];
		Assert(current_char <= gUnicodeMaxLegalUTF32, "Illegal character");
		Assert(current_char < gUnicodeSurrogateHighStart || current_char > gUnicodeSurrogateLowEnd,
			"Illegal character");
		stringUTF32 += current_char;
	}
}

void UTFConvert::FromUTF16ToUTF32(StringUTF32& stringUTF32, const StringUTF16& stringUTF16)
{
	unsigned int source_index = 0;
	CharUTF32 current_char;
	stringUTF32.Allocate(stringUTF32.GetLength() + stringUTF16.GetLength());
	while (source_index < stringUTF16.GetLength())
	{
		current_char = stringUTF16[source_index++];
		if (current_char >= gUnicodeSurrogateHighStart && current_char <= gUnicodeSurrogateHighEnd)
		{
			Assert(source_index < stringUTF16.GetLength(), "Source exhausted");
			CharUTF32 iChar2 = stringUTF16[source_index++];
			Assert(iChar2 >= gUnicodeSurrogateLowStart && iChar2 <= gUnicodeSurrogateLowEnd,
				"Illegal character");
			current_char = ((current_char - gUnicodeSurrogateHighStart) << gHalfShift) + (iChar2 -
				gUnicodeSurrogateLowStart) + gHalfBase;
		}
		else
			Assert(current_char < gUnicodeSurrogateLowStart || current_char > gUnicodeSurrogateLowEnd,
				"Illegal character");
		Assert(current_char < 0x110000, "Illegal character");
		stringUTF32 += current_char;
	}
}

}

/* EOF */
