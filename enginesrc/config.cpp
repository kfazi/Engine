#include "config.hpp"

namespace engine
{

CConfig::CConfig(const CString &cFileName)
{
	Load(cFileName);
}

CConfig::~CConfig()
{
}

void CConfig::Load(const CString &cFileName)
{
}

void CConfig::Save()
{
}

const CString &CConfig::GetValue(const CString &cName, const CString &cDefaultValue)
{
	return cDefaultValue;
}

void CConfig::SetValue(const CString &cName, const CString &cValue)
{
}

void CConfig::SetValue(const CString &cName, const int iValue)
{
}

void CConfig::SetValue(const CString &cName, const unsigned int iValue)
{
}

void CConfig::SetValue(const CString &cName, const double fValue)
{
}

}

/* EOF */
