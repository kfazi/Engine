#ifndef COMMON_STRING_UTF16_HPP
#define COMMON_STRING_UTF16_HPP

#include "../Internal.hpp"
#include "CStringBase.hpp"
#include "TCharTypes.hpp"

namespace Common
{

class CStringUTF8;
class CStringUTF32;

class CStringUTF16: public CStringBase<TCharUTF16>
{
	private:
		typedef CStringBase<TCharUTF16> MyType;

	public:
		CStringUTF16();
		CStringUTF16(unsigned int iCapacity);
		CStringUTF16(const CStringUTF32 &cStringUTF32);
		CStringUTF16(const CStringUTF16 &cStringUTF16);
		CStringUTF16(const CStringUTF8 &cStringUTF8);
		CStringUTF16(const TCharUTF32 *pString);
		CStringUTF16(const TCharUTF32 *pString, unsigned int iLength);
		CStringUTF16(const TCharUTF16 *pString);
		CStringUTF16(const TCharUTF16 *pString, unsigned int iLength);
		CStringUTF16(const TCharUTF8 *pString);
		CStringUTF16(const TCharUTF8 *pString, unsigned int iLength);

		CStringUTF16 &operator += (const CStringUTF32 &cString);
		CStringUTF16 &operator += (const CStringUTF16 &cString);
		CStringUTF16 &operator += (const CStringUTF8 &cString);
		CStringUTF16 &operator += (const TCharUTF32 *pString);
		CStringUTF16 &operator += (const TCharUTF16 *pString);
		CStringUTF16 &operator += (const TCharUTF8 *pString);
		CStringUTF16 &operator += (TCharUTF32 iChar);
		CStringUTF16 &operator += (TCharUTF16 iChar);
		CStringUTF16 &operator += (TCharUTF8 iChar);
};

}

#endif /* COMMON_STRING_UTF16_HPP */

/* EOF */
