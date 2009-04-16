#include "common.hpp"
#include "sqliteconfig.hpp"

namespace engine
{

CSQLiteConfig::CSQLiteConfig(const CString &cFileName): CConfig(cFileName)
{
}

CSQLiteConfig::~CSQLiteConfig()
{
	sqlite3_close(pDataBase);
}

void CSQLiteConfig::Load(const CString &cFileName)
{
	CConfig::Load(cFileName);
	int iResult;
	iResult = sqlite3_open(cFileName.ToUTF8().c_str(), &pDataBase);
	if (iResult)
	{
		/* ERROR */
		sqlite3_close(pDataBase);
	}

	/* Prepare statements */
	iResult = sqlite3_prepare_v2(pDataBase, "", -1, &pSetStatement, NULL);
	iResult = sqlite3_prepare_v2(pDataBase, "", -1, &pGetStatement, NULL);
}

void CSQLiteConfig::Save()
{
	CConfig::Save();
}

const CString &CSQLiteConfig::GetString(const CString &cName, const CString &cDefaultValue)
{
	return cDefaultValue;
}

int CSQLiteConfig::GetInt(const CString &cName, int iDefaultValue)
{
	return iDefaultValue;
}

unsigned int CSQLiteConfig::GetUnsignedInt(const CString &cName, unsigned int iDefaultValue)
{
	return iDefaultValue;
}

double CSQLiteConfig::GetReal(const CString &cName, double fDefaultValue)
{
	return fDefaultValue;
}

void CSQLiteConfig::Set(const CString &cName, const CString &cValue)
{
	CConfig::Set(cName, cValue);
}

void CSQLiteConfig::Set(const CString &cName, int iValue)
{
	CConfig::Set(cName, iValue);
}

void CSQLiteConfig::Set(const CString &cName, unsigned int iValue)
{
	CConfig::Set(cName, iValue);
}

void CSQLiteConfig::Set(const CString &cName, double fValue)
{
	CConfig::Set(cName, fValue);
}

}

/* EOF */
