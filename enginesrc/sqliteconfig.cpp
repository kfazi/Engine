#include "common.hpp"
#include "sqliteconfig.hpp"
#include "useful.hpp"

namespace engine
{

CSQLiteConfig::CSQLiteConfig(const CString &cFileName): CConfig()
{
	m_pDataBase = NULL;
	Load(cFileName, false);
}

CSQLiteConfig::~CSQLiteConfig()
{
	if (IsModified())
		Save();
	Debug("SQLITE CLOSED");
	sqlite3_close(m_pDataBase);
}

void CSQLiteConfig::Load(const CString &cFileName, bool bSave)
{
	if (bSave)
		Save();
	if (m_pDataBase)
		sqlite3_close(m_pDataBase);
	CConfig::Clear();
	CString cUsedFileName;
	/* SQLite uses colon character for special files, so make sure the file name begins with something else. */
	if (cFileName[0] == ':')
		cUsedFileName = CString("./") + cFileName;
	else
		cUsedFileName = cFileName;
	int iResult = sqlite3_open_v2(cUsedFileName.ToUTF8().c_str(), &m_pDataBase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (iResult != SQLITE_OK)
	{
		sqlite3_close(m_pDataBase);
		CErrorStack::Push(CErrorStack::DOES_NOT_EXSISTS, sqlite3_errmsg(m_pDataBase));
	}

	/* Prepare statements */
	const char *pCreateTableSQL = "CREATE TABLE IF NOT EXISTS config\n"\
																"(\n"\
																"	id INTEGER NOT NULL PRIMARY KEY UNIQUE,\n"\
																"	name TEXT NOT NULL UNIQUE,\n"\
																"	value TEXT NOT NULL\n"\
																");";
	const char *pSelectAllDataSQL = "SELECT name, value FROM config;";
	sqlite3_stmt *pCreateTableStatement;
	sqlite3_prepare_v2(m_pDataBase, pCreateTableSQL, -1, &pCreateTableStatement, NULL);
	sqlite3_stmt *pSelectAllDataStatement;
	sqlite3_prepare_v2(m_pDataBase, pSelectAllDataSQL, -1, &pSelectAllDataStatement, NULL);

	/* Create table if it doesn't exist. */
	sqlite3_step(pCreateTableStatement);
	sqlite3_finalize(pCreateTableStatement);

	/* Load all data. */
	do 
	{
		iResult = sqlite3_step(pSelectAllDataStatement);
		if (iResult == SQLITE_ROW)
		{
			CString cName = reinterpret_cast<const char *>(sqlite3_column_text(pSelectAllDataStatement, 0));
			CString cValue = reinterpret_cast<const char *>(sqlite3_column_text(pSelectAllDataStatement, 1));
			Set(cName, cValue);
		}
	}
	while (iResult == SQLITE_ROW);
	sqlite3_finalize(pSelectAllDataStatement);
	SetFileName(cFileName);
}

void CSQLiteConfig::Save()
{
	if (!IsModified())
		return;
	/* Prepare statements */
	const char *pInsertSQL = "INSERT OR REPLACE INTO config(name, value) VALUES(?1, ?2);";
	const char *pBeginSQL = "BEGIN;";
	const char *pCommitSQL = "COMMIT;";
	sqlite3_stmt *pInsertStatement;
	sqlite3_stmt *pBeginStatement;
	sqlite3_stmt *pCommitStatement;
	sqlite3_prepare_v2(m_pDataBase, pInsertSQL, -1, &pInsertStatement, NULL);
	sqlite3_prepare_v2(m_pDataBase, pBeginSQL, -1, &pBeginStatement, NULL);
	sqlite3_prepare_v2(m_pDataBase, pCommitSQL, -1, &pCommitStatement, NULL);

	/* Begin transaction. */
	sqlite3_step(pBeginStatement);
	sqlite3_finalize(pBeginStatement);

	/* Insert/update data. */
	const std::map<CString, CString> &cValues = GetValues();
	for (std::map<CString, CString>::const_iterator cValuesIterator = cValues.begin(); cValuesIterator != cValues.end(); ++cValuesIterator)
	{
		sqlite3_bind_text(pInsertStatement, 1, (*cValuesIterator).first.ToUTF8().c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(pInsertStatement, 2, (*cValuesIterator).second.ToUTF8().c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_step(pInsertStatement);
		sqlite3_reset(pInsertStatement);
	}

	/* Commit transaction. */
	sqlite3_step(pCommitStatement);
	sqlite3_finalize(pCommitStatement);
}

}

/* EOF */
