#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

#include "string.hpp"

namespace engine
{

class CConfig
{
	friend class CCore;

	private:
		CConfig(const CString &cFileName);
		~CConfig();
		void Load(const CString &cFileName);
	public:
		void Save();
		const CString &GetValue(const CString &cName, const CString &cDefaultValue = "");
		void SetValue(const CString &cName, const CString &cValue);
		void SetValue(const CString &cName, const int iValue);
		void SetValue(const CString &cName, const unsigned int iValue);
		void SetValue(const CString &cName, const double fValue);
};

}

#endif /* ENGINE_CONFIG_HPP */

/* EOF */
