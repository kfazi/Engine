#include "loadengine.hpp"
#include <enginemain.hpp>

typedef void (*TEngineCreateFunction)(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv);
TEngineCreateFunction g_pEngineCreate;

#ifdef WINDOWS
#include <windows.h>
HINSTANCE g_pEngineInstance;
#endif /* WINDOWS */

namespace framework
{

void LoadEngine()
{
#ifdef WINDOWS
	g_pEngineInstance = LoadLibraryA(ENGINE_NAME);
	g_pEngineCreate = reinterpret_cast<TEngineCreateFunction>(GetProcAddress(g_pEngineInstance, "Create"));
#endif /* WINDOWS */
}

void RunEngine(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv)
{
	(*g_pEngineCreate)(cEngineMain, iArgc, pArgv);
}

void CloseEngine()
{
#ifdef WINDOWS
	FreeLibrary(g_pEngineInstance);
#endif /* WINDOWS */
}

}

/* EOF */
