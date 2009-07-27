#ifndef FRAMEWORK_ENGINE_MAIN_IMPLEMENTATION_HPP
#define FRAMEWORK_ENGINE_MAIN_IMPLEMENTATION_HPP

#include <enginemain.hpp>

namespace framework
{

class CEngineMainImplementation: public engine::CEngineMain
{
	public:
		virtual ~CEngineMainImplementation();
		virtual void Create();
		virtual void Run();
		virtual void ParseArgument(const engine::CString &cArgumentName, const engine::CString &cArgumentValue);
};

}

#endif /* FRAMEWORK_ENGINE_MAIN_IMPLEMENTATION_HPP */

/* EOF */
