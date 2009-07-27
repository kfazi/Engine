#ifndef FRAMEWORK_LOAD_ENGINE_HPP
#define FRAMEWORK_LOAD_ENGINE_HPP

namespace engine
{

class CEngineMain;

}

namespace framework
{

void LoadEngine();
void RunEngine(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv);
void CloseEngine();

}

#endif /* FRAMEWORK_LOAD_ENGINE_HPP */

/* EOF */
