#include "common.hpp"
#include "config.hpp"
#include "useful.hpp"

namespace engine
{

/* Exceptions. */
CConfig::CException::CException(const CString &cMessage): CEngineException(cMessage) {}
CConfig::CLoadException::CLoadException(const CString &cFileName, const CString &cErrorMessage): CConfig::CException((Format("Can't load %1% configuration file (%2%).") % cFileName % cErrorMessage).str()) {}
CConfig::CSaveException::CSaveException(const CString &cFileName, const CString &cErrorMessage): CConfig::CException((Format("Can't save %1% configuration file (%2%).") % cFileName % cErrorMessage).str()) {}

/* Main code. */
bool CConfig::CopyWithoutBackSlashes(CString &cOutput, const CString &cInput) const
{
	for (unsigned int i = 0; i < cInput.length(); ++i)
	{
		if (cInput[i] == '\\')
			cOutput.push_back('/');
		else
			cOutput.push_back(cInput[i]);
	}
	unsigned int iPosition = cOutput.find_first_of('/');
	if (iPosition == CString::npos)
		return false;
	return true;
}

CConfig::CConfig()
{
	m_bModified = false;
	m_cFileName = "";
}

bool CConfig::IsModified() const
{
	return m_bModified;
}

void CConfig::SetFileName(const CString &cFileName)
{
	m_cFileName = cFileName;
}

void CConfig::Clear()
{
	m_cValues.clear();
}

CConfig::~CConfig()
{
	if (m_bModified)
		Save();
}

const CString &CConfig::GetFileName()
{
	return m_cFileName;
}

const CString &CConfig::GetString(const CString &cName, const CString &cDefaultValue)
{
	std::map<CString, CString>::const_iterator cValuesIterator = m_cValues.find(cName);
	if (cValuesIterator == m_cValues.end())
		return cDefaultValue;
	return ((*cValuesIterator).second);
}

int CConfig::GetInt(const CString &cName, int iDefaultValue)
{
	std::map<CString, CString>::const_iterator cValuesIterator = m_cValues.find(cName);
	if (cValuesIterator == m_cValues.end())
		return iDefaultValue;
	TStringStream tStringStream((*cValuesIterator).second);
	int iResult;
	tStringStream >> iResult;
	if (!tStringStream)
		return iDefaultValue;
	return iResult;
}

unsigned int CConfig::GetUnsignedInt(const CString &cName, unsigned int iDefaultValue)
{
	std::map<CString, CString>::const_iterator cValuesIterator = m_cValues.find(cName);
	if (cValuesIterator == m_cValues.end())
		return iDefaultValue;
	TStringStream tStringStream((*cValuesIterator).second);
	unsigned int iResult;
	tStringStream >> iResult;
	if (!tStringStream)
		return iDefaultValue;
	return iResult;
}

double CConfig::GetReal(const CString &cName, double fDefaultValue)
{
	std::map<CString, CString>::const_iterator cValuesIterator = m_cValues.find(cName);
	if (cValuesIterator == m_cValues.end())
		return fDefaultValue;
	TStringStream tStringStream((*cValuesIterator).second);
	double fResult;
	tStringStream >> fResult;
	if (!tStringStream)
		return fDefaultValue;
	return fResult;
}

void CConfig::Set(const CString &cName, const CString &cValue)
{
	CString cCorrectName;
	if (CopyWithoutBackSlashes(cCorrectName, cName))
	{
		m_cValues[cCorrectName] = cName;
		m_bModified = true;
	}
	else
		Warning(Format("You must specify root category of the variable %1%.") % cName);
}

void CConfig::Set(const CString &cName, int iValue)
{
	CString cCorrectName;
	if (CopyWithoutBackSlashes(cCorrectName, cName))
	{
		TStringStream tStringStream;
		tStringStream << iValue;
		m_cValues[cCorrectName] = tStringStream.str();
		m_bModified = true;
	}
	else
		Warning(Format("You must specify root category of the variable %1%.") % cName);
}

void CConfig::Set(const CString &cName, unsigned int iValue)
{
	CString cCorrectName;
	if (CopyWithoutBackSlashes(cCorrectName, cName))
	{
		TStringStream tStringStream;
		tStringStream << iValue;
		m_cValues[cCorrectName] = tStringStream.str();
		m_bModified = true;
	}
	else
		Warning(Format("You must specify root category of the variable %1%.") % cName);
}

void CConfig::Set(const CString &cName, double fValue)
{
	CString cCorrectName;
	if (CopyWithoutBackSlashes(cCorrectName, cName))
	{
		TStringStream tStringStream;
		tStringStream << fValue;
		m_cValues[cCorrectName] = tStringStream.str();
		m_bModified = true;
	}
	else
		Warning(Format("You must specify root category of the variable %1%.") % cName);
}

}

/* EOF */
