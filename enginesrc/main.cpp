#include "common.hpp"
#include <iostream>
#include <fstream>
#include "core.hpp"
#include "useful.hpp"
#include "engineexception.hpp"
#include "operating_system/systemwindow.hpp"
#include "operating_system/systeminfo.hpp"
#include "string.hpp"

namespace engine
{

class CSimpleLogger
{
	private:
		std::fstream cFile;
	public:
		CSimpleLogger()
		{
			cFile.open("log.txt", std::ios::out);
		}
		~CSimpleLogger()
		{
			cFile.close();
		}
		void Log(const std::string &cMessage, const CLogger::EMessageType eType)
		{
			if (eType == CLogger::FATALERROR)
				CCore::GetInstance()->GetWindow()->MessageBox("Error", cMessage);
			else
				std::cout << cMessage << std::endl;
			cFile << cMessage << std::endl;
			cFile.flush();
		}
};

int DefineEngineMainClass(CEngineMain *pMainClass, int argc, char **argv)
{
	CCore cEngine;
	try
	{
		CCore::Create(&cEngine, ENGINE_DEFAULT_CONFIG_FILE);
		CSimpleLogger cLogger;
		CCore::GetInstance()->GetLogger()->Register(&cLogger, &CSimpleLogger::Log);
		Debug(CCore::GetInstance()->GetSystemInfo()->GetSystemName());
		Debug(Format("Number of processors: %1%") % CCore::GetInstance()->GetSystemInfo()->GetNumberOfProcessors());
		Debug(Format("Total memory: %1%") % CCore::GetInstance()->GetSystemInfo()->GetTotalMemory());
		Debug(Format("Free memory: %1%") % CCore::GetInstance()->GetSystemInfo()->GetFreeMemory());
		//CCore::GetInstance()->GetWindow()->SetResolution(5, false);
		//Debug(Format("Driver name: %1%") % CCore::GetInstance()->GetWindow()->GetDriverName());
		//while (!CCore::GetInstance()->Finished())
		//{
		//	CCore::GetInstance()->ProcessFrame();
		//}
	}
	catch (std::exception &cException)
	{
		std::cout << cException.what() << std::endl;
	}
	return 0;
}

}

/* EOF */
