#include "time.hpp"
#include "common.hpp"
#include <limits>
#include <boost/date_time/microsec_time_clock.hpp>

namespace engine
{

boost::posix_time::ptime CTime::m_cLastTime(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time());
double CTime::m_fFrameTime = 0.0;
double CTime::m_fTotalTime = 0.0;
double CTime::m_fFPSTime = 0.0;
double CTime::m_fFPS = 0.0;
int CTime::m_iFrames = 0;

void CTime::Update()
{
	boost::posix_time::ptime cCurrentTime(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time());
	boost::posix_time::time_duration cTimeDifference = cCurrentTime - m_cLastTime;
	m_fFrameTime = cTimeDifference.total_milliseconds() / 1000.0;
	m_fTotalTime += m_fFrameTime;
	m_fFPSTime += m_fFrameTime;
	++m_iFrames;
	if (m_fFPSTime >= ENGINE_FPS_COUNTER_INTERVAL)
	{
		m_fFPS = m_iFrames / (ENGINE_FPS_COUNTER_INTERVAL * m_fFPSTime);
		m_iFrames = 0;
		m_fFPSTime = 0.0;
	}
#ifdef CONSTRAIN_FPS
	if (m_fFrameTime < std::numeric_limits<double>::epsilon())
		return; /* This computer is too fast, skip assigining cCurrentTime to m_cLastTime. */
#endif /* CONSTRAIN_FPS */
	m_cLastTime = cCurrentTime;
}

}

/* EOF */

