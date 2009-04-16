#ifndef ENGINE_SQLITE_CONFIG_HPP
#define ENGINE_SQLITE_CONFIG_HPP

#include "common.hpp"
#include "config.hpp"
#include "3rdparty/sqlite/sqlite3.h"

namespace engine
{

class CSQLiteConfig: public CConfig
{
	private:
		sqlite3 *pDataBase;
		sqlite3_stmt *pSetStatement;
		sqlite3_stmt *pGetStatement;

	public:
		CSQLiteConfig(const CString &cFileName);
		virtual ~CSQLiteConfig();
		virtual void Load(const CString &cFileName);
		virtual void Save();
		virtual const CString &GetString(const CString &cName, const CString &cDefaultValue = "");
		virtual int GetInt(const CString &cName, int iDefaultValue = 0);
		virtual unsigned int GetUnsignedInt(const CString &cName, unsigned int iDefaultValue = 0);
		virtual double GetReal(const CString &cName, double fDefaultValue = 0.0);
		virtual void Set(const CString &cName, const CString &cValue);
		virtual void Set(const CString &cName, int iValue);
		virtual void Set(const CString &cName, unsigned int iValue);
		virtual void Set(const CString &cName, double fValue);
};

}

#endif /* ENGINE_SQLITE_CONFIG_HPP */

/* EOF */
