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
#include "operating_system/windows/windowssystemdisplaymanager.hpp"
#include "operating_system/windows/windowssystemwindow.hpp"
#include "operating_system/windows/windowssystemmodule.hpp"
#include "operating_system/windows/windowssysteminfo.hpp"
#include "operating_system/unix/unixsystemdirectories.hpp"
#include "operating_system/unix/unixsystemwindow.hpp"
#include "operating_system/unix/unixsysteminfo.hpp"
#include "renderer/renderersmanager.hpp"

void CreateEngine(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv)
{
	engine::CCore *pCore = new engine::CCore;
	engine::CCore::s_pEngine = pCore;
	/* Logger system is used by all other systems. */
	pCore->m_pLogger = new engine::CLogger();
	/* Config system is used by all other systems. */
	pCore->m_pConfig = new engine::CSQLiteConfig(pCore->s_cConfigFile);
	pCore->m_pEngineMain = &cEngineMain;
	pCore->m_pEngineMain->Create();
	/* Ignore executable path/name. */
	for (int i = 1; i < iArgc; ++i)
	{
		engine::CString cArgument = pArgv[i];
		int iEqualSignIndex = cArgument.find_first_of('=');
		if (iEqualSignIndex != engine::CString::npos)
		{
			/* This argument has some value. */
			engine::CString cName = cArgument.substr(0, iEqualSignIndex);
			engine::CString cValue = cArgument.substr(iEqualSignIndex - 1);
			pCore->m_pEngineMain->ParseArgument(cName, cValue);
		}
		else
			pCore->m_pEngineMain->ParseArgument(cArgument, "");
	}
	pCore->Create();
	pCore->m_pEngineMain->ChooseScene();
}

void DestroyEngine()
{
	delete engine::CCore::s_pEngine;
}

namespace engine
{

CString CCore::s_cConfigFile = CString("config.cfg");
CCore *CCore::s_pEngine = NULL;
bool CCore::s_bDebug = true;

CCore::CCore()
{
	m_pLogger = NULL;
	m_pConfig = NULL;
	m_pFunctionManager = NULL;
	m_pSceneManager = NULL;
	m_pSystemDirectories = NULL;
	m_pSystemDisplayManager = NULL;
	m_pSystemModule = NULL;
	m_pSystemInfo = NULL;
	m_pRenderersManager = NULL;
	m_fFrameTime = 0;
	m_bFinished = false;
	CErrorStack::Init();
	CTime::Update();
}

CCore::~CCore()
{
	m_pEngineMain->Destroy();
	delete m_pRenderersManager;
	delete m_pSceneManager;
	delete m_pFunctionManager;
	delete m_pSystemDirectories;
	delete m_pSystemModule;
	delete m_pSystemInfo;
	/* Config system must be deleted just before logger system. */
	delete m_pConfig;
	/* Logger system must be deleted last. */
	delete m_pLogger;
}

void CCore::Create()
{
	/* Function manager must be created before other managers. */
	m_pFunctionManager = new CFunctionManager();
	m_pSceneManager = new CSceneManager();
#ifdef WINDOWS
	m_pSystemDirectories = new CWindowsSystemDirectories();
	m_pSystemDisplayManager = new CWindowsSystemDisplayManager();
	m_pSystemModule = new CWindowsSystemModule();
	m_pSystemInfo = new CWindowsSystemInfo();
#endif /* WINDOWS */
#ifdef UNIX
	m_pSystemDirectories = new CUnixSystemDirectories();
	m_pSystemInfo = new CUnixSystemInfo();
#endif /* UNIX */
	m_pRenderersManager = new CRenderersManager();
	m_fFrameTime = static_cast<double>(ENGINE_FPS);
}

void CCore::ProcessFrame()
{
	static double fFrameWait = 1.0 / static_cast<double>(ENGINE_FPS);
#ifdef ENGINE_CONSTRAIN_FPS
	if (m_fFrameTime < fFrameWait)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>((fFrameWait - m_fFrameTime) * 1000.0)));
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
		Warning("Error stack is not empty!");
		while (CErrorStack::Count() > 0)
		{
			Warning(Format("Code: %1%, Message: %2%") % CErrorStack::Check().eCode % CErrorStack::Check().cMessage);
			CErrorStack::Pop();
		}
		Error("Can't continue!");
	}
#else /* DEBUG */
	CErrorStack::Clear();
#endif /* DEBUG */
	m_pSystemDisplayManager->ProcessEvents();
}

}

/* EOF */

