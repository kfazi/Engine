#include "common.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "core.hpp"
#include "time.hpp"
#include "logger.hpp"
#include "sqliteconfig.hpp"
#include "functionmanager.hpp"
#include "errorstack.hpp"
#include "scene/scenemanager.hpp"
#include "operating_system/systeminput.hpp"
#include "operating_system/windows/windowssystemdirectories.hpp"
#include "operating_system/windows/windowssystemwindow.hpp"
#include "operating_system/windows/windowssysteminfo.hpp"
#include "operating_system/unix/unixsystemdirectories.hpp"
#include "operating_system/unix/unixsystemwindow.hpp"
#include "operating_system/unix/unixsysteminfo.hpp"

namespace engine
{

CCore *CCore::m_pEngine = NULL;
bool CCore::m_bDebug = true;

CCore::CCore()
{
	m_pLogger = NULL;
	m_pConfig = NULL;
	m_pFunctionManager = NULL;
	m_pSceneManager = NULL;
	m_pSystemDirectories = NULL;
	m_pSystemWindow = NULL;
	m_pSystemInfo = NULL;
	CErrorStack::Init();
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

void CCore::Create(CCore *pEngine, const CString &cConfigFile)
{
	/* Logger system is used by all other systems. */
	pEngine->m_pLogger = new CLogger();
	/* Config system is used by all other systems. */
	pEngine->m_pConfig = new CSQLiteConfig(cConfigFile);
	m_pEngine = pEngine;
	/* Function manager must be created before other managers. */
	pEngine->m_pFunctionManager = new CFunctionManager();
	pEngine->m_pSceneManager = new CSceneManager();
#ifdef WINDOWS
	pEngine->m_pSystemDirectories = new CWindowsSystemDirectories();
//	pEngine->m_pSystemWindow = new CWindowsSystemWindow();
	pEngine->m_pSystemInfo = new CWindowsSystemInfo();
#endif /* WINDOWS */
#ifdef UNIX
	pEngine->m_pSystemDirectories = new CUnixSystemDirectories();
	pEngine->m_pSystemWindow = new CUnixSystemWindow();
	pEngine->m_pSystemInfo = new CUnixSystemInfo();
#endif /* UNIX */
	pEngine->m_fFrameTime = 0;
	pEngine->m_bFinished = false;
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
//	m_pSystemWindow->ProcessEvents(); /* Once per frame is enough. */
//	m_pSystemWindow->SwapBuffers();
}

}

/* EOF */

