#include "common.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "core.hpp"
#include "time.hpp"
#include "logger.hpp"
#include "sqliteconfig.hpp"
#include "functionmanager.hpp"
#include "errorstack.hpp"
#include "enginemain.hpp"
#include "scene/scenemanager.hpp"
#include "operating_system/systeminput.hpp"
#include "operating_system/windows/windowssystemdirectories.hpp"
#include "operating_system/windows/windowssystemwindow.hpp"
#include "operating_system/windows/windowssysteminfo.hpp"
#include "operating_system/unix/unixsystemdirectories.hpp"
#include "operating_system/unix/unixsystemwindow.hpp"
#include "operating_system/unix/unixsysteminfo.hpp"

void Create(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv)
{
	cEngineMain.Create();
	/* Ignore executable path/name. */
	for (int i = 1; i < iArgc; ++i)
	{
		engine::CString cArgument = pArgv[i];
		int iEqualSignIndex = cArgument.find_first_of('=');
		if (iEqualSignIndex != engine::CString::npos)
		{
			/* This argument has a value. */
			engine::CString cName = cArgument.substr(0, iEqualSignIndex);
			engine::CString cValue = cArgument.substr(iEqualSignIndex - 1);
			cEngineMain.ParseArgument(cName, cValue);
		}
		else
			cEngineMain.ParseArgument(cArgument, engine::CString(""));
	}
	engine::CCore cCore;
	/* Run application */
	cEngineMain.Run();
}

namespace engine
{

CString CCore::m_cConfigFile = CString("config.cfg");
CCore *CCore::m_pEngine = NULL;
bool CCore::m_bDebug = true;

CCore::CCore()
{
	m_pEngine = this;
	m_pLogger = NULL;
	m_pConfig = NULL;
	m_pFunctionManager = NULL;
	m_pSceneManager = NULL;
	m_pSystemDirectories = NULL;
	m_pSystemWindow = NULL;
	m_pSystemInfo = NULL;
	CErrorStack::Init();
	/* Logger system is used by all other systems. */
	m_pEngine->m_pLogger = new CLogger();
	/* Config system is used by all other systems. */
	m_pEngine->m_pConfig = new CSQLiteConfig(m_cConfigFile);
	/* Function manager must be created before other managers. */
	m_pEngine->m_pFunctionManager = new CFunctionManager();
	m_pEngine->m_pSceneManager = new CSceneManager();
#ifdef WINDOWS
	m_pEngine->m_pSystemDirectories = new CWindowsSystemDirectories();
	//	pEngine->m_pSystemWindow = new CWindowsSystemWindow();
	m_pEngine->m_pSystemInfo = new CWindowsSystemInfo();
#endif /* WINDOWS */
#ifdef UNIX
	m_pEngine->m_pSystemDirectories = new CUnixSystemDirectories();
	m_pEngine->m_pSystemWindow = new CUnixSystemWindow();
	m_pEngine->m_pSystemInfo = new CUnixSystemInfo();
#endif /* UNIX */
	m_pEngine->m_fFrameTime = 0;
	m_pEngine->m_bFinished = false;
}

CCore::~CCore()
{
	if (m_pEngine)
	{
		delete m_pSceneManager;
		delete m_pFunctionManager;
		delete m_pSystemDirectories;
//		delete m_pSystemWindow;
		delete m_pSystemInfo;
		/* Config system must be deleted just before logger system. */
		delete m_pConfig;
		/* Logger system must be deleted last. */
		delete m_pLogger;
	}
}

void CCore::ProcessFrame()
{
	static double fFrameWait = 1.0 / ENGINE_FPS;
#ifdef ENGINE_CONSTRAIN_FPS
	if (m_fFrameTime < fFrameWait)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>((fFrameWait - m_fFrameTime) * static_cast<double>(1000.0))));
		CTime::Update();
		m_fFrameTime += CTime::GetFrameTime();
	}
#else /* ENGINE_CONSTRAIN_FPS */
	CTime::Update();
	m_fFrameTime += CTime::GetFrameTime();
#endif /* ENGINE_CONSTRAIN_FPS */
	while (m_fFrameTime >= fFrameWait)
	{
		m_pFunctionManager->Process();
		m_fFrameTime -= fFrameWait;
	}
#ifdef _DEBUG
	if (CErrorStack::Count() > 0)
	{
		exit(-1);
	}
#else /* DEBUG */
	CErrorStack::Clear();
#endif /* DEBUG */
//	m_pSystemWindow->ProcessEvents(); /* Once per frame is enough. */
//	m_pSystemWindow->SwapBuffers();
}

}

/* EOF */

