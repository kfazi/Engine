#ifdef WINDOWS

#ifndef ENGINE_WINDOWS_SYSTEM_MODULE_HPP
#define ENGINE_WINDOWS_SYSTEM_MODULE_HPP

#include "../../common.hpp"
#include "../../string.hpp"
#include "../systemmodule.hpp"

namespace engine
{

class CWindowsSystemModule: public CSystemModule
{
	friend class CCore;

	public:
		CWindowsSystemModule();
		virtual ~CWindowsSystemModule();
		virtual CString GetSystemName(const CString &cDirectory, const CString &cFileName);
		virtual unsigned int Load(const CString &cFileName);
		virtual void *GetSymbol(const unsigned int iModuleId, const CString &cSymbolName);
		virtual void Close(const unsigned int iModuleId);
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_MODULE_HPP */

#endif /* WINDOWS */

/* EOF */
