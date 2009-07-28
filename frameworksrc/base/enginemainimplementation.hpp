#ifndef FRAMEWORK_ENGINE_MAIN_IMPLEMENTATION_HPP
#define FRAMEWORK_ENGINE_MAIN_IMPLEMENTATION_HPP

#include <enginemain.hpp>
#include <iostream>
#include <fstream>

namespace framework
{

class CEngineMainImplementation: public engine::CEngineMain
{
	private:
		std::fstream m_cLogFile;
		void BasicLog(const engine::CString &cMessage, const engine::CLogger::EMessageType);

	public:
		virtual ~CEngineMainImplementation();
		virtual void Create();
		virtual void Destroy();
		virtual void ChooseScene();
		virtual void ParseArgument(const engine::CString &cArgumentName, const engine::CString &cArgumentValue);
};

}

#endif /* FRAMEWORK_ENGINE_MAIN_IMPLEMENTATION_HPP */

/* EOF */
