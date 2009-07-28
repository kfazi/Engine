#ifndef ENGINE_MAIN
#define ENGINE_MAIN

#include "engine.hpp"

namespace engine
{

class CEngineMain
{
	public:
		virtual ~CEngineMain()
		{
		}
		virtual void Create() = 0;
		virtual void Destroy() = 0;
		virtual void ChooseScene() = 0;
		virtual void ParseArgument(const CString &cArgumentName, const CString &cArgumentValue) = 0;
};

}

#endif /* ENGINE_MAIN */

/* EOF */
