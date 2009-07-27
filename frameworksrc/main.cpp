#ifdef UNIX

#include "enginemainimplementation.hpp"
#include "loadengine.hpp"

int main(int argc, char **argv)
{
	CEngineMainImplementation cEngineMain;
	framework::LoadEngine();
	framework::RunEngine(cEngineMain, argc, argv);
	framework::CloseEngine();
	return 0;
}

#endif /* UNIX */

/* EOF */
