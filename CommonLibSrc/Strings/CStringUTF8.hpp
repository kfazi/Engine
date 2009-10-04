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
	public:
		CStringUTF8();
		CStringUTF8(unsigned int iCapacity);
		CStringUTF8(const CStringUTF32 &cStringUTF32);
		CStringUTF8(const CStringUTF16 &cStringUTF16);
		CStringUTF8(const CStringUTF8 &cStringUTF8);
		CStringUTF8(const TCharUTF32 *pString);
		CStringUTF8(const TCharUTF16 *pString);
		CStringUTF8(const TCharUTF8 *pString);
};

}

#endif /* COMMON_STRING_UTF8_HPP */

/* EOF */
