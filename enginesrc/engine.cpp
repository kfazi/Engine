#include "engine.hpp"
#include "config.hpp"
#include "time.hpp"
#include "common.hpp"
#include "logger.hpp"
#include "functionmanager.hpp"
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
	m_fFrameTime = 0;
}

CEngine::~CEngine()
{
	delete m_pSceneManager;
	delete m_pFunctionManager;
	/* Logger system must be deleted last. */
	delete m_pLogger;
}

void CEngine::ProcessFrame()
{
	static double fFrameWait = 1.0 / ENGINE_FPS;
	CTime::Update();
	m_fFrameTime += CTime::GetFrameTime();
#if 0
	if (m_fFrameTime < fFrameWait)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>((fFrameWait - m_fFrameTime) * static_cast<double>(1000.0))));
		CTime::Update();
		m_fFrameTime += CTime::GetFrameTime();
	}
#endif
	while (m_fFrameTime >= fFrameWait)
	{
		m_pFunctionManager->Process();
		m_fFrameTime -= fFrameWait;
	}
}

}

/* EOF */

