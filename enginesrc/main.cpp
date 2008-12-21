#include <iostream>
#include <fstream>
#include "engine.hpp"
#include "useful.hpp"
#include "engineexception.hpp"
#include "operating_system/systemwindow.hpp"
#include "operating_system/systeminfo.hpp"

using namespace engine;

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
			if (eType == CLogger::ERROR)
				CEngine::GetInstance()->GetWindow()->MessageBox("Error", cMessage);
			else
				std::cout << cMessage << std::endl;
			cFile << cMessage << std::endl;
			cFile.flush();
		}
};

int main()
{
	CEngine cEngine;
	try
	{
		CEngine::Create(&cEngine);
		CSimpleLogger cLogger;
		CEngine::GetInstance()->GetLogger()->Register(&cLogger, &CSimpleLogger::Log);
		Debug(CEngine::GetInstance()->GetSystemInfo()->GetSystemName());
		Debug(Format("Number of processors: %1%") % CEngine::GetInstance()->GetSystemInfo()->GetNumberOfProcessors());
		Debug(Format("Total memory: %1%") % CEngine::GetInstance()->GetSystemInfo()->GetTotalMemory());
		Debug(Format("Free memory: %1%") % CEngine::GetInstance()->GetSystemInfo()->GetFreeMemory());
		CEngine::GetInstance()->GetWindow()->SetResolution(5, false);
		Debug(Format("Driver name: %1%") % CEngine::GetInstance()->GetWindow()->GetDriverName());
		while (!CEngine::GetInstance()->Finished())
		{
			CEngine::GetInstance()->ProcessFrame();
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

