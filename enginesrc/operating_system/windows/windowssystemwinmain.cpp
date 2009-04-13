#ifdef WINDOWS

#include <windows.h>

namespace engine
{

extern int DefineEngineMainClass(int argc, char **argv);

int DefineEngineMainClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	int iResult = DefineEngineMainClass(iArgc, pArgv);
	for (int i = 0; i < iArgc; ++i)
		delete [] pArgv[i];
	delete [] pArgv;

	return iResult;
}

}

#endif /* WINDOWS */

/* EOF */
