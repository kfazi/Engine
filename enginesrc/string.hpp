#ifndef ENGINE_STRING_HPP
#define ENGINE_STRING_HPP

#include "common.hpp"
#include <string>
#include <sstream>

namespace engine
{

#if ENGINE_STRING_CHAR == 0
typedef unsigned int TChar;
#elif ENGINE_STRING_CHAR == 1
typedef unsigned short TChar;
#else
#error Wrong ENGINE_STRING_CHAR value.
#endif /* ENGINE_STRING_CHAR */

typedef std::basic_istringstream<TChar, std::char_traits<TChar>, std::allocator<TChar> > TIStringStream;
typedef std::basic_ostringstream<TChar, std::char_traits<TChar>, std::allocator<TChar> > TOStringStream;
typedef std::basic_stringstream<TChar, std::char_traits<TChar>, std::allocator<TChar> > TStringStream;

class DLLEXPORTIMPORT CString: public std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >
{
	private:
		typedef std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> > TUTF16String;
		typedef std::basic_string<unsigned int, std::char_traits<unsigned int>, std::allocator<unsigned int> > TUTF32String;

		static const char s_aTrailingBytesForUTF8[];
		static const unsigned int s_aOffsetsFromUTF8[];
		static const unsigned int s_aFirstByteMark[];

		static unsigned int UTF16strlen(const unsigned short *pUTF16String);
		static unsigned int UTF32strlen(const unsigned int *pUTF32String);
		static bool IsLegalUTF8(const char *pSource, int iLength);

		void AppendFromUTF8ToUTF16(TUTF16String &cTarget, const char *pUTF8String, unsigned int iLength) const;
		void AppendFromUTF32ToUTF16(TUTF16String &cTarget, const unsigned int *pUTF32String, unsigned int iLength) const;
		void AppendFromUTF8ToUTF32(TUTF32String &cTarget, const char *pUTF8String, unsigned int iLength) const;
		void AppendFromUTF16ToUTF32(TUTF32String &cTarget, const unsigned short *pUTF16String, unsigned int iLength) const;

		void AppendFromUTF8(const char *pUTF8String, unsigned int iLength);
		void AppendFromUTF16(const unsigned short *pUTF16String, unsigned int iLength);
		void AppendFromUTF32(const unsigned int *pUTF32String, unsigned int iLength);

	public:
		CString();
		CString(const std::basic_string<TChar> &cString);
		CString(const std::string &cUTF8String);
		CString(const char *pUTF8String, unsigned int iLength);
		CString(const char *pUTF8String);
		CString(const unsigned short *pUTF16String, unsigned int iLength);
		CString(const unsigned short *pUTF16String);
		CString(const unsigned int *pUTF32String, unsigned int iLength);
		CString(const unsigned int *pUTF32String);
		CString(const wchar_t *pUTFString, unsigned int iLength);
		CString(const wchar_t *pUTFString);
		std::string ToUTF8() const;
		void ToUTF8(std::string &cUTF8String) const;
		TUTF16String ToUTF16() const;
		void ToUTF16(TUTF16String &cUTF16String) const;
		TUTF32String ToUTF32() const;
		void ToUTF32(TUTF32String &cUTF32String) const;
		std::wstring ToWCHAR() const;
		void ToWCHAR(std::wstring &cUTFString) const;
		static CString FromUTF8(const std::string &cUTF8String);
		static CString FromUTF8(const char *pUTF8String, unsigned int iLength);
		static CString FromUTF8(const char *pUTF8String);
		static CString FromUTF16(const std::string &cUTF16String);
		static CString FromUTF16(const unsigned short *pUTF16String, unsigned int iLength);
		static CString FromUTF16(const unsigned short *pUTF16String);
		static CString FromUTF32(const std::string &cUTF32String);
		static CString FromUTF32(const unsigned int *pUTF32String, unsigned int iLength);
		static CString FromUTF32(const unsigned int *pUTF32String);
		static CString FromWCHAR(const std::string &cUTFString);
		static CString FromWCHAR(const wchar_t *pUTFString, unsigned int iLength);
		static CString FromWCHAR(const wchar_t *pUTFString);

		CString &operator = (const std::string &cUTF8String);
		CString &operator = (const char *pUTF8String);
		CString &operator = (const unsigned short *pUTF16String);
		CString &operator = (const unsigned int *pUTF32String);
		CString &operator = (const wchar_t *pUTFString);

		CString &operator += (const std::string &cUTF8String);
		CString &operator += (const CString &cString);
		CString &operator += (const char *pUTF8String);
		CString &operator += (const unsigned short *pUTF16String);
		CString &operator += (const unsigned int *pUTF32String);
		CString &operator += (const wchar_t *pUTFString);

		CString operator + (const std::string &cUTF8String);
		CString operator + (const CString &cString);
		CString operator + (const char *pUTF8String);
		CString operator + (const unsigned short *pUTF16String);
		CString operator + (const unsigned int *pUTF32String);
		CString operator + (const wchar_t *pUTFString);
};

}

#endif /* ENGINE_STRING_HPP */

/* EOF */