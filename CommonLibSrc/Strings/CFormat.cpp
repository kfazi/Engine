#include "../Internal.hpp"
#include "CFormat.hpp"
#include "CStringConvert.hpp"

namespace Common
{

CFormat::CFormat(const CString &cString): m_cUnformattedBuffer(cString)
{
}

const CString &CFormat::Get() const
{
	if (!m_pBuffer)
		;
	return *m_pBuffer;
}

const TChar *CFormat::GetRaw() const
{
	return Get().GetRaw();
}

}

/* EOF */
