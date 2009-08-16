#include "common.hpp"
#include "string.hpp"
#include <algorithm>
#include <cstring>
#include <boost/regex.hpp>

/* http://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.c */

namespace engine
{

const char CString::s_aTrailingBytesForUTF8[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};

const unsigned int CString::s_aOffsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL };

const unsigned int CString::s_aFirstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

typedef boost::cpp_regex_traits<TChar> TCharCPPRegexTraits;
typedef boost::regex_traits<TChar, TCharCPPRegexTraits> TCharRegexTraits;
typedef boost::basic_regex<TChar, TCharRegexTraits> TCharRegex;
typedef boost::match_results<const TChar *> TCharMatchResults;

unsigned int CString::UTF16strlen(const unsigned short *pUTF16String)
{
	const unsigned short *pCounter = pUTF16String;
	while (*pCounter)
		pCounter++;
	return pCounter - pUTF16String;
}

unsigned int CString::UTF32strlen(const unsigned int *pUTF32String)
{
	const unsigned int *pCounter = pUTF32String;
	while (*pCounter)
		pCounter++;
	return pCounter - pUTF32String;
}

bool CString::IsLegalUTF8(const char *pSource, int iLength)
{
	unsigned int iChar;
	const char *pSourceEnd = pSource + iLength;
	switch (iLength)
	{
		default:
			return false;
			/* Everything else falls through when "true"... */
		case 4:
			if ((iChar = (*--pSourceEnd)) < 0x80 || iChar > 0xBF)
				return false;
		case 3:
			if ((iChar = (*--pSourceEnd)) < 0x80 || iChar > 0xBF)
				return false;
		case 2:
			if ((iChar = (*--pSourceEnd)) > 0xBF)
				return false;
			switch (*pSource)
			{
				/* no fall-through in this inner switch */
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
			if (*pSource >= 0x80 && *pSource < 0xC2)
				return false;
	}
	if (*pSource > 0xF4)
		return false;
	return true;
}

void CString::AppendFromUTF8ToUTF16(TUTF16String &cTarget, const char *pUTF8String, unsigned int iLength) const
{
	unsigned int iChar;
	const char *pSource = pUTF8String;
	const char *pSourceEnd = pUTF8String + iLength;
	while (pSource < pSourceEnd)
	{
		iChar = 0;
		unsigned short iExtraBytesToRead = s_aTrailingBytesForUTF8[*pSource];
		if (pSource + iExtraBytesToRead >= pSourceEnd)
		{
			//result = sourceExhausted; break;
		}
		/* Do this check whether lenient or strict */
		if (!IsLegalUTF8(pSource, iExtraBytesToRead + 1))
		{
			//result = sourceIllegal;
			break;
		}
		/*
		* The cases all fall through. See "Note A" below.
		*/
		switch (iExtraBytesToRead)
		{
			default:
			case 5:
			case 4:
				//result = sourceIllegal;
				break;
			case 3:
				iChar += *pSource++;
				iChar <<= 6;
			case 2:
				iChar += *pSource++;
				iChar <<= 6;
			case 1:
				iChar += *pSource++;
				iChar <<= 6;
			case 0:
				iChar += *pSource++;
		}
		iChar -= s_aOffsetsFromUTF8[iExtraBytesToRead];

		if (iChar <= 0x0000FFFFUL)
		{ /* Target is a character <= 0xFFFF */
			/* UTF-16 surrogate values are illegal in UTF-32 */
			if (iChar >= 0xD800UL && iChar <= 0xDFFFUL)
			{
				//result = sourceIllegal;
			}
			else
			{
				cTarget.push_back(static_cast<unsigned short>(iChar)); /* normal case */
			}
		}
		else if (iChar > 0x0010FFFFUL)
		{
			//result = sourceIllegal;
		}
		else
		{
			iChar -= 0x0010000UL;
			cTarget.push_back(static_cast<unsigned short>((iChar >> 10) + 0xD800UL));
			cTarget.push_back(static_cast<unsigned short>((iChar & 0x3FFUL) + 0xDC00UL));
		}
	}
}

void CString::AppendFromUTF32ToUTF16(TUTF16String &cTarget, const unsigned int *pUTF32String, unsigned int iLength) const
{
	unsigned int iChar;
	const unsigned int *pSource = pUTF32String;
	const unsigned int *pSourceEnd = pUTF32String + iLength;

	while (pSource < pSourceEnd)
	{
		iChar = *pSource++;
		if (iChar <= 0x0000FFFFUL)
		{ /* Target is a character <= 0xFFFF */
			/* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
			if (iChar >= 0xD800UL && iChar <= 0xDFFFUL)
			{
					//result = sourceIllegal;
				break;
			}
			else
			{
				cTarget.push_back(static_cast<unsigned short >(iChar));
			}
		}
		else if (iChar > 0x0010FFFFUL)
		{
			//result = sourceIllegal;
		}
		else
		{
			/* target is a character in range 0xFFFF - 0x10FFFF. */
			iChar -= 0x0010000UL;
			cTarget.push_back(static_cast<unsigned short >((iChar >> 10) + 0xD800UL));
			cTarget.push_back(static_cast<unsigned short >((iChar & 0x3FFUL) + 0xDC00UL));
		}
	}
}

void CString::AppendFromUTF8ToUTF32(TUTF32String &cTarget, const char *pUTF8String, unsigned int iLength) const
{
	unsigned int iChar;
	const char *pSource = pUTF8String;
	const char *pSourceEnd = pUTF8String + iLength;
	while (pSource < pSourceEnd)
	{
		iChar = 0;
		unsigned short iExtraBytesToRead = s_aTrailingBytesForUTF8[*pSource];
		if (pSource + iExtraBytesToRead >= pSourceEnd)
		{
			//result = sourceExhausted; break;
		}
		/* Do this check whether lenient or strict */
		if (!IsLegalUTF8(pSource, iExtraBytesToRead+1))
		{
			//result = sourceIllegal;
			break;
		}
		/*
		* The cases all fall through. See "Note A" below.
		*/
		switch (iExtraBytesToRead)
		{
			default:
			case 5:
			case 4:
				/* ERROR */
				break;
			case 3:
				iChar += *pSource++;
				iChar <<= 6;
			case 2:
				iChar += *pSource++;
				iChar <<= 6;
			case 1:
				iChar += *pSource++;
				iChar <<= 6;
			case 0:
				iChar += *pSource++;
		}
		iChar -= s_aOffsetsFromUTF8[iExtraBytesToRead];

		if (iChar <= 0x0010FFFFUL)
		{
			/*
			* UTF-16 surrogate values are illegal in UTF-32, and anything
			* over Plane 17 (> 0x10FFFF) is illegal.
			*/
			if (iChar >= 0xD800UL && iChar <= 0xDFFFUL)
			{
				//source -= (extraBytesToRead+1); /* return to the illegal value itself */
			}
			else
			{
				cTarget.push_back(iChar);
			}
		}
		else
		{ /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
			//result = sourceIllegal;
		}
	}
}

void CString::AppendFromUTF16ToUTF32(TUTF32String &cTarget, const unsigned short *pUTF16String, unsigned int iLength) const
{
	unsigned int iChar;
	unsigned int iChar2;
	const unsigned short *pSource = pUTF16String;
	const unsigned short *pSourceEnd = pUTF16String + iLength;
	while (pSource < pSourceEnd)
	{
		iChar = *pSource++;
		/* If we have a surrogate pair, convert to UTF32 first. */
		if (iChar >= 0xD800UL && iChar <= 0xDBFFUL)
		{
			/* If the 16 bits following the high surrogate are in the source buffer... */
			if (pSource < pSourceEnd)
			{
				iChar2 = *pSource;
				/* If it's a low surrogate, convert to UTF32. */
				if (iChar2 >= 0xDC00UL && iChar2 <= 0xDFFFUL)
				{
					iChar = ((iChar - 0xD800UL) << 10) + (iChar2 - 0xDC00UL) + 0x0010000UL;
					++pSource;
				}
				else
				{
					/* String is broken */
					break;
				}
			}
			else
			{ /* We don't have the 16 bits following the high surrogate. */
				/* String is broken */
				break;
			}
		}
		else
		{
			/* UTF-16 surrogate values are illegal in UTF-32 */
			if (iChar >= 0xDC00UL && iChar <= 0xDFFFUL)
			{
				/* String is broken */
				break;
			}
		}
		cTarget.push_back(iChar);
	}
}

void CString::AppendFromUTF8(const char *pUTF8String, unsigned int iLength)
{
#if ENGINE_STRING_CHAR == 0
	AppendFromUTF8ToUTF32(*this, pUTF8String, iLength);
#else
	AppendFromUTF8ToUTF16(*this, pUTF8String, iLength);
#endif /* ENGINE_STRING_CHAR */
}

void CString::AppendFromUTF16(const unsigned short *pUTF16String, unsigned int iLength)
{
#if ENGINE_STRING_CHAR == 0
	AppendFromUTF16ToUTF32(*this, pUTF16String, iLength);
#else
	for (unsigned int i = 0; i < iLength; ++i)
		push_back(pUTF16String[i]);
#endif /* ENGINE_STRING_CHAR */
}

void CString::AppendFromUTF32(const unsigned int *pUTF32String, unsigned int iLength)
{
#if ENGINE_STRING_CHAR == 0
	for (unsigned int i = 0; i < iLength; ++i)
		push_back(pUTF32String[i]);
#else
	AppendFromUTF32ToUTF16(*this, pUTF32String, iLength);
#endif /* ENGINE_STRING_CHAR */
}

CString::CString()
{
}

CString::CString(const std::basic_string<TChar> &cString)
{
	std::copy(cString.begin(), cString.end(), std::back_inserter(*this));
}

CString::CString(const std::string &cUTF8String)
{
	AppendFromUTF8(cUTF8String.c_str(), cUTF8String.length());
}

CString::CString(const std::wstring &cUTFString)
{
#if WCHAR_SIZE == 2
	AppendFromUTF16(reinterpret_cast<const unsigned short *>(cUTFString.c_str()), cUTFString.length());
#else
	AppendFromUTF32(reinterpret_cast<const unsigned int *>(cUTFString.c_str()), cUTFString.length());
#endif /* WCHAR_SIZE == 2 */
}

CString::CString(const char *pUTF8String, unsigned int iLength)
{
	AppendFromUTF8(pUTF8String, iLength);
}

CString::CString(const char *pUTF8String)
{
	AppendFromUTF8(pUTF8String, strlen(pUTF8String));
}

CString::CString(const unsigned short *pUTF16String, unsigned int iLength)
{
	AppendFromUTF16(pUTF16String, iLength);
}

CString::CString(const unsigned short *pUTF16String)
{
	AppendFromUTF16(pUTF16String, UTF16strlen(pUTF16String));
}

CString::CString(const unsigned int *pUTF32String, unsigned int iLength)
{
	AppendFromUTF32(pUTF32String, iLength);
}

CString::CString(const unsigned int *pUTF32String)
{
	AppendFromUTF32(pUTF32String, UTF32strlen(pUTF32String));
}

CString::CString(const wchar_t *pUTFString, unsigned int iLength)
{
#if WCHAR_SIZE == 2
	AppendFromUTF16(reinterpret_cast<const unsigned short *>(pUTFString), iLength);
#else
	AppendFromUTF32(reinterpret_cast<const unsigned int *>(pUTFString), iLength);
#endif /* WCHAR_SIZE == 2 */
}

CString::CString(const wchar_t *pUTFString)
{
#if WCHAR_SIZE == 2
	AppendFromUTF16(reinterpret_cast<const unsigned short *>(pUTFString), UTF16strlen(reinterpret_cast<const unsigned short *>(pUTFString)));
#else
	AppendFromUTF32(reinterpret_cast<const unsigned int *>(pUTFString), UTF32strlen(reinterpret_cast<const unsigned int *>(pUTFString)));
#endif /* WCHAR_SIZE == 2 */
}

std::string CString::ToUTF8() const
{
	std::string cResult;
	ToUTF8(cResult);
	return cResult;
}

void CString::ToUTF8(std::string &cUTF8String) const
{
	cUTF8String.clear();
	unsigned int iChar;
	CString::const_iterator cSourceIterator = begin();
	while (cSourceIterator != end())
	{
		unsigned int iBytesToWrite = 0;
		const unsigned int iByteMask = 0x7F; /* WAS 0xBF, TODO: INVESTIGATE!!! */
		const unsigned int iByteMark = 0x80; 
		iChar = *cSourceIterator++;
#if ENGINE_STRING_CHAR == 0
		/* UTF-16 surrogate values are illegal in UTF-32 */
		if (iChar >= 0xD800UL && iChar <= 0xDFFFUL)
		{
			//result = sourceIllegal;
			break;
		}
#else
		/* If we have a surrogate pair, convert to UTF32 first. */
		if (iChar >= 0xD800UL && iChar <= 0xDBFFUL)
		{
			/* If the 16 bits following the high surrogate are in the source buffer... */
			if (cSourceIterator != end())
			{
				unsigned int iChar2 = *cSourceIterator;
				/* If it's a low surrogate, convert to UTF32. */
				if (iChar2 >= 0xDC00UL && iChar2 <= 0xDFFFUL)
				{
					iChar = ((iChar - 0xD800UL) << 10) + (iChar2 - 0xDC00UL) + 0x0010000UL;
					++cSourceIterator;
				}
				else
				{
					//result = sourceIllegal;
					break;
				}
			}
			else
			{ /* We don't have the 16 bits following the high surrogate. */
				//result = sourceExhausted;
				break;
			}
		}
		else if (iChar >= 0xDC00UL && iChar <= 0xDFFFUL)
		{
			//result = sourceIllegal;
			break;
		}
#endif /* ENGINE_STRING_CHAR */
		/* Figure out how many bytes the result will require */
		if (iChar < 0x80UL)
			iBytesToWrite = 1;
		else if (iChar < 0x800UL)
			iBytesToWrite = 2;
		else if (iChar < 0x10000UL)
			iBytesToWrite = 3;
		else if (iChar < 0x110000UL)
			iBytesToWrite = 4;
		else
		{
			/* ERROR */
		}

		switch (iBytesToWrite)
		{ /* note: everything falls through. */
			case 4:
				cUTF8String.push_back(static_cast<char>(((iChar >> 18) | iByteMark) & iByteMask));
			case 3:
				cUTF8String.push_back(static_cast<char>(((iChar >> 12) | iByteMark) & iByteMask));
			case 2:
				cUTF8String.push_back(static_cast<char>(((iChar >> 6) | iByteMark) & iByteMask));
			case 1:
				cUTF8String.push_back(static_cast<char>((iChar | s_aFirstByteMark[iBytesToWrite]) & iByteMask));
		}
	}
}

CString::TUTF16String CString::ToUTF16() const
{
	TUTF16String cResult;
	ToUTF16(cResult);
	return cResult;
}

void CString::ToUTF16(TUTF16String &cUTF16String) const
{
#if ENGINE_STRING_CHAR == 0
	AppendFromUTF32ToUTF16(cUTF16String, c_str(), length());
#else
	std::copy(begin(), end(), cUTF16String.begin());
#endif /* ENGINE_STRING_CHAR */
}

CString::TUTF32String CString::ToUTF32() const
{
	TUTF32String cResult;
	ToUTF32(cResult);
	return cResult;
}

void CString::ToUTF32(TUTF32String &cUTF32String) const
{
#if ENGINE_STRING_CHAR == 0
	std::copy(begin(), end(), cUTF32String.begin());
#else
	AppendFromUTF16ToUTF32(cUTF32String, c_str(), length());
#endif /* ENGINE_STRING_CHAR */
}

std::wstring CString::ToWCHAR() const
{
#if WCHAR_SIZE == 2
	std::basic_string<wchar_t> cResult;
	ToWCHAR(cResult);
	return cResult;
#else
	return reinterpret_cast<std::basic_string<wchar_t> >(ToUTF32());
#endif /* WCHAR_SIZE == 2 */
}

void CString::ToWCHAR(std::wstring &cUTFString) const
{
#if WCHAR_SIZE == 2
#if ENGINE_STRING_CHAR == 0
	TUTF16String cUTF16String;
	AppendFromUTF32ToUTF16(cUTF16String, c_str(), length());
	cUTFString = reinterpret_cast<const wchar_t *>(cUTF16String.c_str());
#else
	cUTFString = reinterpret_cast<const wchar_t *>(c_str());
#endif /* ENGINE_STRING_CHAR == 0 */
#else
#if ENGINE_STRING_CHAR == 0
	cUTFString = reinterpret_cast<const wchar_t *>(c_str());
#else
	TUTF32String cUTF32String;
	AppendFromUTF16ToUTF32(cUTF32String, c_str(), length());
	cUTFString = reinterpret_cast<const wchar_t *>(cUTF32String.c_str());
#endif /* ENGINE_STRING_CHAR == 0 */
#endif /* WCHAR_SIZE == 2 */
}

CString CString::FromUTF8(const std::string &cUTF8String)
{
	return CString(cUTF8String.c_str(), cUTF8String.length());
}

CString CString::FromUTF8(const char *pUTF8String, unsigned int iLength)
{
	return CString(pUTF8String, iLength);
}

CString CString::FromUTF8(const char *pUTF8String)
{
	return CString(pUTF8String, strlen(pUTF8String));
}

CString CString::FromUTF16(const std::string &cUTF16String)
{
	return CString(reinterpret_cast<const unsigned short *>(cUTF16String.c_str()), cUTF16String.length());
}

CString CString::FromUTF16(const unsigned short *pUTF16String, unsigned int iLength)
{
	return CString(pUTF16String, iLength);
}

CString CString::FromUTF16(const unsigned short *pUTF16String)
{
	return CString(pUTF16String);
}

CString CString::FromUTF32(const std::string &cUTF32String)
{
	return CString(reinterpret_cast<const unsigned int *>(cUTF32String.c_str()), cUTF32String.length());
}

CString CString::FromUTF32(const unsigned int *cUTF32String, unsigned int iLength)
{
	return CString(cUTF32String, iLength);
}

CString CString::FromUTF32(const unsigned int *cUTF32String)
{
	return CString(cUTF32String);
}

CString CString::FromWCHAR(const std::string &cUTFString)
{
	return CString(reinterpret_cast<const wchar_t *>(cUTFString.c_str()), cUTFString.length());
}

CString CString::FromWCHAR(const wchar_t *pUTFString, unsigned int iLength)
{
	return CString(pUTFString, iLength);
}

CString CString::FromWCHAR(const wchar_t *pUTFString)
{
	return CString(pUTFString);
}

TFormat CString::Format(const CString &cFormat)
{
	return TFormat(cFormat);
}

bool CString::MatchRegex(const CString &cRegex) const
{
	TCharMatchResults cMatch;
	return boost::regex_match(c_str(), cMatch, TCharRegex(cRegex), boost::regex_constants::match_not_dot_null);
}

CString CString::SecureRegex() const
{
	CString cResult = boost::regex_replace(*this, TCharRegex(CString("\\$")), CString("$$"), boost::regex_constants::match_not_dot_null | boost::regex_constants::format_literal);
	cResult = boost::regex_replace(cResult, TCharRegex(CString("\\\\")), CString("\\\\"), boost::regex_constants::match_not_dot_null | boost::regex_constants::format_literal);
	cResult = boost::regex_replace(cResult, TCharRegex(CString("\\:")), CString("\\:"), boost::regex_constants::match_not_dot_null | boost::regex_constants::format_literal);
	cResult = boost::regex_replace(cResult, TCharRegex(CString("\\?")), CString("\\?"), boost::regex_constants::match_not_dot_null | boost::regex_constants::format_literal);
	cResult = boost::regex_replace(cResult, TCharRegex(CString("\\(")), CString("\\("), boost::regex_constants::match_not_dot_null | boost::regex_constants::format_literal);
	cResult = boost::regex_replace(cResult, TCharRegex(CString("\\)")), CString("\\)"), boost::regex_constants::match_not_dot_null | boost::regex_constants::format_literal);
	return cResult;
}

CString &CString::operator = (const std::string &cUTF8String)
{
	*this = FromUTF8(cUTF8String);
	return *this;
}

CString &CString::operator = (const char *pUTF8String)
{
	*this = FromUTF8(pUTF8String);
	return *this;
}

CString &CString::operator = (const unsigned short *pUTF16String)
{
	*this = FromUTF16(pUTF16String);
	return *this;
}

CString &CString::operator = (const unsigned int *pUTF32String)
{
	clear();
	AppendFromUTF32(pUTF32String, UTF32strlen(pUTF32String));
	return *this;
}

CString &CString::operator = (const wchar_t *pUTFString)
{
	clear();
#if WCHAR_SIZE == 2
	AppendFromUTF16(reinterpret_cast<const unsigned short *>(pUTFString), UTF16strlen(reinterpret_cast<const unsigned short *>(pUTFString)));
#else
	AppendFromUTF32(reinterpret_cast<const unsigned int *>(pUTFString), UTF32strlen(reinterpret_cast<const unsigned int *>(pUTFString)));
#endif /* WCHAR_SIZE == 2 */
	return *this;
}

CString &CString::operator += (const std::string &cUTF8String)
{
	AppendFromUTF8(cUTF8String.c_str(), cUTF8String.length());
	return *this;
}

CString &CString::operator += (const CString &cString)
{
	for (CString::const_iterator cStringIterator = cString.begin(); cStringIterator != cString.end(); ++cStringIterator)
		push_back(*cStringIterator);
	return *this;
}

CString &CString::operator += (const char *pUTF8String)
{
	AppendFromUTF8(pUTF8String, strlen(pUTF8String));
	return *this;
}

CString &CString::operator += (const unsigned short *pUTF16String)
{
	AppendFromUTF16(pUTF16String, UTF16strlen(pUTF16String));
	return *this;
}

CString &CString::operator += (const unsigned int *pUTF32String)
{
	AppendFromUTF32(pUTF32String, UTF32strlen(pUTF32String));
	return *this;
}

CString &CString::operator += (const wchar_t *pUTFString)
{
#if WCHAR_SIZE == 2
	AppendFromUTF16(reinterpret_cast<const unsigned short *>(pUTFString), UTF16strlen(reinterpret_cast<const unsigned short *>(pUTFString)));
#else
	AppendFromUTF32(reinterpret_cast<const unsigned int *>(pUTFString), UTF32strlen(reinterpret_cast<const unsigned int *>(pUTFString)));
#endif /* WCHAR_SIZE == 2 */
	return *this;
}

CString CString::operator + (const std::string &cUTF8String)
{
	CString cResult(*this);
	cResult += cUTF8String;
	return cResult;
}

CString CString::operator + (const CString &cString)
{
	CString cResult(*this);
	cResult += cString;
	return cResult;
}

CString CString::operator + (const char *pUTF8String)
{
	CString cResult(*this);
	cResult += pUTF8String;
	return cResult;
}

CString CString::operator + (const unsigned short *pUTF16String)
{
	CString cResult(*this);
	cResult += pUTF16String;
	return cResult;
}

CString CString::operator + (const unsigned int *pUTF32String)
{
	CString cResult(*this);
	cResult += pUTF32String;
	return cResult;
}

CString CString::operator + (const wchar_t *pUTFString)
{
	CString cResult(*this);
	cResult += pUTFString;
	return cResult;
}

}

/* EOF */