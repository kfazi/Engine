#ifdef WINDOWS

#include "../../common.hpp"
#include "../../useful.hpp"
#include "../../core.hpp"
#include "../systemmodule.hpp"
#include "../systemdirectories.hpp"
#include "windowssystemmodule.hpp"
#include "windowssystemerrormessages.hpp"
#include <Windows.h>
#include <string>

namespace engine
{

void CWindowsSystemModule::UnloadModule(SModule *pModule)
{
	if (!FreeLibrary(static_cast<HMODULE>(pModule->pHandle)))
		Error(Format("CWindowsSystemModule::Close - Can't close module %1% (%2%)") % pModule->cName % CWindowsSystemErrorMessages::GetError(GetLastError()));
}

CWindowsSystemModule::CWindowsSystemModule(unsigned int iAllocationBase): CSystemModule(iAllocationBase)
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
		cResult += cFileName;
	else
	{
		if (cFileName.substr(0, 3) != CString("lib"))
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
	HINSTANCE pHandle = LoadLibraryW(cFileName.ToWCHAR().c_str());
	if (!pHandle)
		Error(Format("CWindowsSystemModule::Load - Can't load module %1% (%2%)") % cFileName % CWindowsSystemErrorMessages::GetError(GetLastError()));
	SModule *pModule = new SModule(cFileName, pHandle);
	iResult = AddModule(pModule);
	return iResult;
}

void *CWindowsSystemModule::GetSymbol(const unsigned int iModuleId, const CString &cSymbolName)
{
	SModule *pModule = GetModule(iModuleId);
	void *pSymbol = GetProcAddress(static_cast<HMODULE>(pModule->pHandle), cSymbolName.ToUTF8().c_str());
	if (!pSymbol)
		Debug((Format("CWindowsSystemModule::GetSymbol - Symbol %1% not found in module %2%.") % cSymbolName % pModule->cName).str());
	return pSymbol;
}

}

#endif /* WINDOWS */

/* EOF */
