#ifndef COMMON_STRING_UTF8_HPP
#define COMMON_STRING_UTF8_HPP

#include "../Internal.hpp"
#include "CStringBase.hpp"
#include "TCharTypes.hpp"

namespace Common
{

class CStringUTF16;
class CStringUTF32;

class CStringUTF8: public CStringBase<TCharUTF8>
{
	private:
		typedef CStringBase<TCharUTF8> MyType;

	public:
		CStringUTF8();
		CStringUTF8(unsigned int iCapacity);
		CStringUTF8(const CStringUTF32 &cStringUTF32);
		CStringUTF8(const CStringUTF16 &cStringUTF16);
		CStringUTF8(const CStringUTF8 &cStringUTF8);
		CStringUTF8(const TCharUTF32 *pString);
		CStringUTF8(const TCharUTF32 *pString, unsigned int iLength);
		CStringUTF8(const TCharUTF16 *pString);
		CStringUTF8(const TCharUTF16 *pString, unsigned int iLength);
		CStringUTF8(const TCharUTF8 *pString);
		CStringUTF8(const TCharUTF8 *pString, unsigned int iLength);

		CStringUTF8 &operator += (const CStringUTF32 &cString);
		CStringUTF8 &operator += (const CStringUTF16 &cString);
		CStringUTF8 &operator += (const CStringUTF8 &cString);
		CStringUTF8 &operator += (const TCharUTF32 *pString);
		CStringUTF8 &operator += (const TCharUTF16 *pString);
		CStringUTF8 &operator += (const TCharUTF8 *pString);
		CStringUTF8 &operator += (TCharUTF32 iChar);
		CStringUTF8 &operator += (TCharUTF16 iChar);
		CStringUTF8 &operator += (TCharUTF8 iChar);
};

}

#endif /* COMMON_STRING_UTF8_HPP */

/* EOF */
