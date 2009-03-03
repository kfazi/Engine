#ifdef WINDOWS

#include "windowssystemdirectories.hpp"
#include "../../3rdparty/utf8.h"

namespace engine
{

CWindowsSystemDirectories::CWindowsSystemDirectories(): CSystemDirectories()
{
	std::string cTempPath;

	/* Get executable path, so it can be used when SHGetKnownFolderPath or SHGetFolderPath fails */
	char aExecutablePath[MAX_PATH + 1];
	::GetModuleFileName(NULL, aExecutablePath, MAX_PATH);
	aExecutablePath[MAX_PATH] = 0;

#ifndef __MINGW32__
	PWSTR pLocalAppDataPath;
	if (::SHGetKnownFolderPath(::FOLDERID_LocalAppData, KF_FLAG_CREATE | KF_FLAG_DEFAULT_PATH | KF_FLAG_NOT_PARENT_RELATIVE, NULL, &pLocalAppDataPath) == S_OK)
	{
		std::wstring cLocalAppDataPath = pLocalAppDataPath;
		utf8::utf16to8(cLocalAppDataPath.begin(), cLocalAppDataPath.end(), std::back_inserter(cTempPath));
		::CoTaskMemFree(pLocalAppDataPath);
	}
	else
		cTempPath = aExecutablePath;
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
	cTempPath = aExecutablePath;
	SetExecutablePath(cTempPath);

	/* Resources path */
	SetResourcesPath(cTempPath + "\\Data");
}

}

#endif /* WINDOWS */

/* EOF */
