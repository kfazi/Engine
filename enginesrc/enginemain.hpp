#ifndef ENGINE_MAIN
#define ENGINE_MAIN

#include "engine.hpp"

#ifdef WINDOWS
#include <windows.h>
#define DEFINE_ENGINE_MAIN_CLASS(CClass) \
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) \
	{ \
		return engine::DefineEngineMainClass(CClass, hInstance, hPrevInstance, lpCmdLine, nCmdShow); \
	}
#else
#define DEFINE_ENGINE_MAIN_CLASS(CClass) \
	int main(int argc, char **argv)
	{ \
		return engine::DefineEngineMainClass(CClass, argc, argv); \
	}
#endif /* WINDOWS */

namespace engine
{

class CEngineMain
{
	public:
		virtual void ParseArgument(const CString &cArgumentName, const CString &cArgumentValue);
};

}
#endif /* ENGINE_MAIN */

/* EOF */
