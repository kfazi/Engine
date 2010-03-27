#include "../Internal.hpp"
#include "Format.hpp"
//#include "StringConvert.hpp"

namespace Common
{

CFormat::CFormat(const String& cString): m_cUnformattedBuffer(cString)
{
}

const String& CFormat::Get() const
{
	if (!m_pBuffer)
		;
	return *m_pBuffer;
}

const Char *CFormat::GetRaw() const
{
	return Get().GetRaw();
}

}

/* EOF */
