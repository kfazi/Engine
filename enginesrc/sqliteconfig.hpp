#ifndef ENGINE_SQLITE_CONFIG_HPP
#define ENGINE_SQLITE_CONFIG_HPP

#include "common.hpp"
#include "useful.hpp"
#include "config.hpp"
#include "3rdparty/sqlite/sqlite3.h"

namespace engine
{

class CSQLiteConfig: public CConfig
{
	private:
		sqlite3 *m_pDataBase;

		bool ExecuteSQLStatement(sqlite3_stmt *pStatement);

	public:
		CSQLiteConfig(const CString &cFileName);
		virtual ~CSQLiteConfig();
		virtual void Load(const CString &cFileName, bool bSave = true);
		virtual void Save();
};

}

#endif /* ENGINE_SQLITE_CONFIG_HPP */

/* EOF */
