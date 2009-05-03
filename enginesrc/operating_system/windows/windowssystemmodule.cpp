#ifdef WINDOWS

#include "../../common.hpp"
#include "../../useful.hpp"
#include "../../core.hpp"
#include "../systemmodule.hpp"
#include "../systemdirectories.hpp"
#include "windowssystemmodule.hpp"
#include <windows.h>
#include <string>

namespace engine
{

CWindowsSystemModule::CWindowsSystemModule()
{
}

CWindowsSystemModule::~CWindowsSystemModule()
{
}

CString CWindowsSystemModule::GetSystemName(const CString &cDirectory, const CString &cFileName)
{
	CString cResult = cDirectory;
	CCore::GetInstance()->GetSystemDirectories()->CorrectPath(cResult);
	if (cFileName.substr(cFileName.length() - 5, 4) == CString(".dll"))
	{
		cResult += cFileName;
	}
	else if (cFileName.substr(0, 3) == CString("lib"))
	{
		cResult += cFileName;
		cResult += CString(".dll");
	}
	else
	{
		cResult += CString("lib");
		cResult += cFileName;
		cResult += CString(".dll");
	}
	return cResult;
}

unsigned int CWindowsSystemModule::Load(const CString &cFileName)
{
	unsigned int iResult;
	if (FindModule(iResult, cFileName))
		return iResult;
	std::basic_string<unsigned short> cFileName16 = cFileName.ToUTF16();
	HINSTANCE pHandle = LoadLibraryW(reinterpret_cast<const wchar_t *>(cFileName16.c_str()));
	if (!pHandle)
		;/* ERROR */
	SModule *pModule = new SModule(cFileName, pHandle);
	iResult = AddModule(pModule);
	return iResult;
}

void *CWindowsSystemModule::GetSymbol(const unsigned int iModuleId, const CString &cSymbolName)
{
	SModule *pModule = GetModule(iModuleId);
	void *pSymbol = GetProcAddress(static_cast<HMODULE>(pModule->pHandle), cSymbolName.ToUTF8().c_str());
	if (!pSymbol)
		Debug((Format("Symbol %1% not found in module %2%.") % cSymbolName % pModule->cName).str());
	return pSymbol;
}

void CWindowsSystemModule::Close(const unsigned int iModuleId)
{
	SModule *pModule = GetModule(iModuleId);
	pModule->iReferences--;
	if (!FreeLibrary(static_cast<HMODULE>(pModule->pHandle)))
		; /* ERROR */
	if (!pModule->iReferences)
	{
		RemoveModule(iModuleId);
		delete pModule;
	}
}

}

#endif /* WINDOWS */

/* EOF */
