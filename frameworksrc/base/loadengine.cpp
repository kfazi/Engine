#include "loadengine.hpp"
#include <enginemain.hpp>

typedef void (*TEngineCreateFunction)(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv);
TEngineCreateFunction g_pEngineCreate;
typedef void (*TEngineDestroyFunction)();
TEngineDestroyFunction g_pEngineDestroy;

#ifdef WINDOWS
#include <Windows.h>
HINSTANCE g_pEngineInstance;
#endif /* WINDOWS */

namespace framework
{

void LoadEngine()
{
#ifdef WINDOWS
	g_pEngineInstance = LoadLibraryA(ENGINE_NAME);
	g_pEngineCreate = reinterpret_cast<TEngineCreateFunction>(GetProcAddress(g_pEngineInstance, "CreateEngine"));
	g_pEngineDestroy = reinterpret_cast<TEngineDestroyFunction>(GetProcAddress(g_pEngineInstance, "DestroyEngine"));
#endif /* WINDOWS */
}

void RunEngine(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv)
{
	(*g_pEngineCreate)(cEngineMain, iArgc, pArgv);
	/* Run application */
	while (!engine::CCore::GetInstance()->IsFinished())
	{
		engine::CCore::GetInstance()->ProcessFrame();
	}
	engine::CCore::GetInstance()->GetLogger()->Log("Engine exited normally.");
	(*g_pEngineDestroy)();
}

void CloseEngine()
{
#ifdef WINDOWS
	FreeLibrary(g_pEngineInstance);
#endif /* WINDOWS */
}

}

/* EOF */
