#ifdef WINDOWS

#include <Windows.h>

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	return TRUE;
}

BOOL APIENTRY DllEntryPoint(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	return TRUE;
}

#endif /* WINDOWS */

/* EOF */
