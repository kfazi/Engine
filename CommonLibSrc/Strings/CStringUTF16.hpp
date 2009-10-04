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
	public:
		CStringUTF16();
		CStringUTF16(unsigned int iCapacity);
		CStringUTF16(const CStringUTF32 &cStringUTF32);
		CStringUTF16(const CStringUTF16 &cStringUTF16);
		CStringUTF16(const CStringUTF8 &cStringUTF8);
		CStringUTF16(const TCharUTF32 *pString);
		CStringUTF16(const TCharUTF16 *pString);
		CStringUTF16(const TCharUTF8 *pString);
};

}

#endif /* COMMON_STRING_UTF16_HPP */

/* EOF */
