#include "engine.hpp"
#include "config.hpp"
#include "time.hpp"
#include "common.hpp"
#include "logger.hpp"
#include "functionmanager.hpp"
#include "operating_system/unix/unixsystemwindow.hpp"
#include "operating_system/unix/unixsysteminfo.hpp"
#include "scene/scenemanager.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

namespace engine
{

CEngine *CEngine::m_pEngine = NULL;

CEngine::CEngine()
{
	m_pLogger = NULL;
	m_pFunctionManager = NULL;
	m_pSceneManager = NULL;
	m_pSystemWindow = NULL;
	m_pSystemInfo = NULL;
}

CEngine::~CEngine()
{
	if (m_pEngine)
	{
		delete m_pSceneManager;
		delete m_pFunctionManager;
		delete m_pSystemWindow;
		delete m_pSystemInfo;
		/* Logger system must be deleted last. */
		delete m_pLogger;
	}
}

void CEngine::Create(CEngine *pEngine)
{
	/* Logger system is used by all other systems. */
	pEngine->m_pLogger = new CLogger();
	m_pEngine = pEngine;
	/* Function manager must be created before other managers. */
	pEngine->m_pFunctionManager = new CFunctionManager();
	pEngine->m_pSceneManager = new CSceneManager();
	pEngine->m_pSystemWindow = new CUnixSystemWindow();
	pEngine->m_pSystemInfo = new CUnixSystemInfo();
	pEngine->m_fFrameTime = 0;
	pEngine->m_bFinished = false;
}

void CEngine::ProcessFrame()
{
	static double fFrameWait = 1.0 / ENGINE_FPS;
#ifdef CONSTRAIN_FPS
	if (m_fFrameTime < fFrameWait)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>((fFrameWait - m_fFrameTime) * static_cast<double>(1000.0))));
		CTime::Update();
		m_fFrameTime += CTime::GetFrameTime();
	}
#else /* CONSTRAIN_FPS */
	CTime::Update();
	m_fFrameTime += CTime::GetFrameTime();
#endif /* CONSTRAIN_FPS */
	while (m_fFrameTime >= fFrameWait)
	{
		m_pFunctionManager->Process();
		m_fFrameTime -= fFrameWait;
	}
	m_pSystemWindow->ProcessEvents(); /* Once per frame is enough. */
	m_pSystemWindow->SwapBuffers();
}

}

/* EOF */

