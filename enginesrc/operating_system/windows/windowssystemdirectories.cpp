#ifdef WINDOWS

#include <Windows.h>
#include <Shlobj.h>
#include <Shlwapi.h>
#include "../../common.hpp"
#include "windowssystemdirectories.hpp"
#include "../../string.hpp"

namespace engine
{

CWindowsSystemDirectories::CWindowsSystemDirectories(): CSystemDirectories()
{
	CString cTempPath;

	/* Get executable path, so it can be used when SHGetKnownFolderPath or SHGetFolderPath fails */
	WCHAR aExecutablePath[MAX_PATH + 1];
	unsigned int iLastChar = ::GetModuleFileName(NULL, aExecutablePath, MAX_PATH);
	if (iLastChar > MAX_PATH - 1)
		iLastChar = MAX_PATH - 1;
	aExecutablePath[iLastChar + 1] = 0;
	::PathRemoveFileSpec(aExecutablePath);
#ifndef __MINGW32__
	PWSTR pLocalAppDataPath;
	if (::SHGetKnownFolderPath(::FOLDERID_LocalAppData, KF_FLAG_CREATE | KF_FLAG_DEFAULT_PATH | KF_FLAG_NOT_PARENT_RELATIVE, NULL, &pLocalAppDataPath) == S_OK)
	{
		cTempPath = reinterpret_cast<unsigned short *>(pLocalAppDataPath);
		::CoTaskMemFree(pLocalAppDataPath);
	}
	else
		cTempPath = reinterpret_cast<unsigned short *>(aExecutablePath);
#else
	char aPath[MAX_PATH + 1];
	if (SUCCEEDED(::SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, aPath)))
	{
		aPath[MAX_PATH] = 0;
		cTempPath = aPath;
	}
	else
		cTempPath = aExecutablePath;
#endif /* __MINGW32__ */
	cTempPath += "\\";
	cTempPath += COMPANY_NAME;
	cTempPath += "\\";
	cTempPath += GAME_NAME;

	/* Config path */
	SetConfigPath(cTempPath + "\\Config");
	/* Mods path */
	SetModsPath(cTempPath + "\\Mods");
	/* Saves path */
	SetSavesPath(cTempPath + "\\Saves");

	/* Executable path */
	cTempPath = reinterpret_cast<unsigned short *>(aExecutablePath);
	SetExecutablePath(cTempPath);

	/* Resources path */
	SetResourcesPath(cTempPath + "\\Data");
}

void CWindowsSystemDirectories::CorrectPath(CString &cPath)
{
	for (unsigned int i = 0; i < cPath.length(); ++i)
	{
		if (cPath[i] == '/')
			cPath[i] = '\\';
	}
	if (cPath[cPath.length() - 1] != '\\')
		cPath.push_back('\\');
}

CString CWindowsSystemDirectories::GetLibraryPrefix() const
{
	return "";
}

CString CWindowsSystemDirectories::GetLibraryPostfix() const
{
	return ".dll";
}

}

#endif /* WINDOWS */

/* EOF */
