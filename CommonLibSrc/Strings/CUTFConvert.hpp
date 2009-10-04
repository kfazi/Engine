#ifndef COMMON_UTF_CONVERT_HPP
#define COMMON_UTF_CONVERT_HPP

#include "../Internal.hpp"

namespace Common
{

class CStringUTF8;
class CStringUTF16;
class CStringUTF32;

class CUTFConvert
{
	private:
		CUTFConvert();
		~CUTFConvert();
		static bool IsLegalUTF8(const CStringUTF8 &cStringUTF8, unsigned int iIndex, unsigned int iBytesToRead);

	public:
		static void FromUTF16ToUTF8(CStringUTF8 &cStringUTF8, const CStringUTF16 &cStringUTF16);
		static void FromUTF32ToUTF8(CStringUTF8 &cStringUTF8, const CStringUTF32 &cStringUTF32);
		static void FromUTF8ToUTF16(CStringUTF16 &cStringUTF16, const CStringUTF8 &cStringUTF8);
		static void FromUTF32ToUTF16(CStringUTF16 &cStringUTF16, const CStringUTF32 &cStringUTF32);
		static void FromUTF8ToUTF32(CStringUTF32 &cStringUTF32, const CStringUTF8 &cStringUTF8);
		static void FromUTF16ToUTF32(CStringUTF32 &cStringUTF32, const CStringUTF16 &cStringUTF16);
};

}

#endif /* COMMON_UTF_CONVERT_HPP */

/* EOF */
