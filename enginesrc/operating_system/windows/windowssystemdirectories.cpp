#include "windowssystemdirectories.hpp"
#include "../../3rdparty/utf8.h"

namespace engine
{

CWindowsSystemDirectories::CWindowsSystemDirectories(): CSystemDirectories()
{
	std::string cTempPath;
	PWSTR pLocalAppDataPath;
	if (::SHGetKnownFolderPath(::FOLDERID_LocalAppData, KF_FLAG_CREATE | KF_FLAG_DEFAULT_PATH | KF_FLAG_NOT_PARENT_RELATIVE, NULL, &pLocalAppDataPath) == S_OK)
	{
		std::wstring cLocalAppDataPath = pLocalAppDataPath;
		utf8::utf16to8(cLocalAppDataPath.begin(), cLocalAppDataPath.end(), std::back_inserter(cTempPath));
		cTempPath += "\\";
		cTempPath += COMPANY_NAME;
		cTempPath += "\\";
		cTempPath += GAME_NAME;
		::CoTaskMemFree(pLocalAppDataPath);
	}
	/* Config path */
	SetConfigPath(cTempPath + "\\Config");
	/* Mods path */
	SetModsPath(cTempPath + "\\Mods");
	/* Saves path */
	SetSavesPath(cTempPath + "\\Saves");

	/* Executable path */
	char aExecutablePath[MAX_PATH + 1];
	::GetModuleFileName(NULL, aExecutablePath, MAX_PATH);
	aExecutablePath[MAX_PATH] = 0;
	cTempPath = aExecutablePath;
	SetExecutablePath(cTempPath);

	/* Resources path */
	SetResourcesPath(cTempPath + "\\Data");
}

}

/* EOF */
