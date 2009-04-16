#include "common.hpp"
#include "config.hpp"

namespace engine
{

CConfig::CConfig(const CString &cFileName)
{
	m_bModified = false;
	Load(cFileName);
}

CConfig::~CConfig()
{
	if (m_bModified)
		Save();
}

void CConfig::Load(const CString &cFileName)
{
	if (m_bModified)
		Save();
}

void CConfig::Save()
{
	m_bModified = false;
}

void CConfig::Set(const CString &cName, const CString &cValue)
{
	m_bModified = true;
}

void CConfig::Set(const CString &cName, int iValue)
{
	m_bModified = true;
}

void CConfig::Set(const CString &cName, unsigned int iValue)
{
	m_bModified = true;
}

void CConfig::Set(const CString &cName, double fValue)
{
	m_bModified = true;
}

}

/* EOF */
