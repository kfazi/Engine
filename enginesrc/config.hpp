#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

#include "common.hpp"
#include "string.hpp"

namespace engine
{

class CConfig
{
	private:
		bool m_bModified;

	protected:
		CConfig(const CString &cFileName);

	public:
		virtual ~CConfig();
		virtual void Load(const CString &cFileName);
		virtual void Save();
		virtual const CString &GetString(const CString &cName, const CString &cDefaultValue = "") = 0;
		virtual int GetInt(const CString &cName, int iDefaultValue = 0) = 0;
		virtual unsigned int GetUnsignedInt(const CString &cName, unsigned int iDefaultValue = 0) = 0;
		virtual double GetReal(const CString &cName, double fDefaultValue = 0.0) = 0;
		virtual void Set(const CString &cName, const CString &cValue);
		virtual void Set(const CString &cName, int iValue);
		virtual void Set(const CString &cName, unsigned int iValue);
		virtual void Set(const CString &cName, double fValue);
};

}

#endif /* ENGINE_CONFIG_HPP */

/* EOF */
