#ifdef WINDOWS

#include "enginemainimplementation.hpp"
#include "loadengine.hpp"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int iArgc;
	WCHAR *pCommandLine;

	pCommandLine = GetCommandLineW();	
	LPWSTR *pArgw = CommandLineToArgvW(pCommandLine, &iArgc);
	char **pArgv = new char *[iArgc + 1];

	for (int i = 0; i < iArgc; ++i)
	{
		int iBufferSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pArgw[i], -1, NULL, 0, NULL, NULL);
		pArgv[i] = new char[iBufferSize];		
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pArgw[i], -1, pArgv[i], iBufferSize, NULL, NULL);
	}
	LocalFree(pArgw);

	framework::CEngineMainImplementation cEngineMain;
	framework::LoadEngine();
	framework::RunEngine(cEngineMain, iArgc, pArgv);

	for (int i = 0; i < iArgc; ++i)
		delete [] pArgv[i];
	delete [] pArgv;

	framework::CloseEngine();

	return 0;
}

#endif /* WINDOWS */

/* EOF */
