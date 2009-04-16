#ifndef ENGINE_MAIN
#define ENGINE_MAIN

#include "engine.hpp"

namespace engine
{

class CEngineMain
{
	private:
		static CCore cEngine;
		void InitCore();
	public:
		CEngineMain();
		void Run();
		virtual void ParseArgument(const CString &cArgumentName, const CString &cArgumentValue);
};

}

#ifdef WINDOWS
//#include <windows.h>
//#undef MessageBox
extern int engine::DefineEngineMainClass(engine::CEngineMain *pMainClass, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#define DEFINE_ENGINE_MAIN_CLASS(CClass) \
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) \
	{ \
		return engine::DefineEngineMainClass(CClass, hInstance, hPrevInstance, lpCmdLine, nCmdShow); \
	}
#else
extern int engine::DefineEngineMainClass(engine::CEngineMain *pMainClass, int argc, char **argv);
#define DEFINE_ENGINE_MAIN_CLASS(CClass) \
	int main(int argc, char **argv)
	{ \
		return engine::DefineEngineMainClass(CClass, argc, argv); \
	}
#endif /* WINDOWS */

#endif /* ENGINE_MAIN */

/* EOF */
