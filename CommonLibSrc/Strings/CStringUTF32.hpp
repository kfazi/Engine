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
	public:
		CStringUTF32();
		CStringUTF32(unsigned int iCapacity);
		CStringUTF32(const CStringUTF32 &cStringUTF32);
		CStringUTF32(const CStringUTF16 &cStringUTF16);
		CStringUTF32(const CStringUTF8 &cStringUTF8);
		CStringUTF32(const TCharUTF32 *pString);
		CStringUTF32(const TCharUTF16 *pString);
		CStringUTF32(const TCharUTF8 *pString);
};

}

#endif /* COMMON_STRING_UTF32_HPP */

/* EOF */
