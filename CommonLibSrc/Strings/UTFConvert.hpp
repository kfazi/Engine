#ifndef COMMON_UTF_CONVERT_HPP
#define COMMON_UTF_CONVERT_HPP

#include "../Internal.hpp"

namespace Common
{

class StringUTF8;
class StringUTF16;
class StringUTF32;

class UTFConvert
{
	private:
		UTFConvert();
		~UTFConvert();
		static bool IsLegalUTF8(const StringUTF8& stringUTF8, size_t index, int bytesToRead);

	public:
		static void FromUTF16ToUTF8(StringUTF8& stringUTF8, const StringUTF16& stringUTF16);
		static void FromUTF32ToUTF8(StringUTF8& stringUTF8, const StringUTF32& stringUTF32);
		static void FromUTF8ToUTF16(StringUTF16& stringUTF16, const StringUTF8& stringUTF8);
		static void FromUTF32ToUTF16(StringUTF16& stringUTF16, const StringUTF32& stringUTF32);
		static void FromUTF8ToUTF32(StringUTF32& stringUTF32, const StringUTF8& stringUTF8);
		static void FromUTF16ToUTF32(StringUTF32& stringUTF32, const StringUTF16& stringUTF16);
};

}

#endif /* COMMON_UTF_CONVERT_HPP */

/* EOF */
