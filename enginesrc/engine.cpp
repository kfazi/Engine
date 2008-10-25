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

CEngine CEngine::cEngine;

CEngine::CEngine()
{
	/* Logger system is used by all other systems. */
	m_pLogger = new CLogger();
	/* Function manager must be created before other managers. */
	m_pFunctionManager = new CFunctionManager();
	m_pSceneManager = new CSceneManager();
	m_pSystemWindow = new CUnixSystemWindow();
	m_pSystemInfo = new CUnixSystemInfo();
	m_fFrameTime = 0;
	m_bFinished = false;
}

CEngine::~CEngine()
{
	delete m_pSceneManager;
	delete m_pFunctionManager;
	delete m_pSystemWindow;
	delete m_pSystemInfo;
	/* Logger system must be deleted last. */
	delete m_pLogger;
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

