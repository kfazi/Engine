#ifndef COMMON_STRING_UTF32_HPP
#define COMMON_STRING_UTF32_HPP

#include "../Internal.hpp"
#include "CStringBase.hpp"
#include "TCharTypes.hpp"

namespace Common
{

class CStringUTF8;
class CStringUTF16;

class CStringUTF32: public CStringBase<TCharUTF32>
{
	private:
		typedef CStringBase<TCharUTF32> MyType;

	public:
		CStringUTF32();
		CStringUTF32(unsigned int iCapacity);
		CStringUTF32(const CStringUTF32& cStringUTF32);
		CStringUTF32(const CStringUTF16& cStringUTF16);
		CStringUTF32(const CStringUTF8& cStringUTF8);
		CStringUTF32(const TCharUTF32* pString);
		CStringUTF32(const TCharUTF32* pString, unsigned int iLength);
		CStringUTF32(const TCharUTF16* pString);
		CStringUTF32(const TCharUTF16* pString, unsigned int iLength);
		CStringUTF32(const TCharUTF8* pString);
		CStringUTF32(const TCharUTF8* pString, unsigned int iLength);

		CStringUTF32& operator += (const CStringUTF32& cString);
		CStringUTF32& operator += (const CStringUTF16& cString);
		CStringUTF32& operator += (const CStringUTF8& cString);
		CStringUTF32& operator += (const TCharUTF32* pString);
		CStringUTF32& operator += (const TCharUTF16* pString);
		CStringUTF32& operator += (const TCharUTF8* pString);
		CStringUTF32& operator += (TCharUTF32 iChar);
		CStringUTF32& operator += (TCharUTF16 iChar);
		CStringUTF32& operator += (TCharUTF8 iChar);
};

}

#endif /* COMMON_STRING_UTF32_HPP */

/* EOF */
