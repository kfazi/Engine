#include "time.hpp"
#include "common.hpp"
#include <limits>
#include <boost/date_time/microsec_time_clock.hpp>

namespace kfz
{

boost::posix_time::ptime CTime::m_cLastTime(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time());
real CTime::m_fFrameTime = TO_REAL(0.0);
real CTime::m_fTotalTime = TO_REAL(0.0);
real CTime::m_fFPSTime = TO_REAL(0.0);
real CTime::m_fFPS = TO_REAL(0.0);
int CTime::m_iFrames = 0;

void CTime::Update()
{
	boost::posix_time::ptime cCurrentTime(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time());
	boost::posix_time::time_duration cTimeDifference = cCurrentTime - m_cLastTime;
	m_fFrameTime = cTimeDifference.total_milliseconds() / TO_REAL(1000.0);
	if (m_fFrameTime < std::numeric_limits<real>::epsilon())
		return; /* This computer is too fast, skip assigining cCurrentTime to m_cLastTime. */
	m_fTotalTime += m_fFrameTime;
	m_cLastTime = cCurrentTime;
	++m_iFrames;
	m_fFPSTime += m_fFrameTime;
	if (m_fFPSTime >= TO_REAL(KFZ_FPS_COUNTER_INTERVAL))
	{
		m_fFPS = m_iFrames / (TO_REAL(KFZ_FPS_COUNTER_INTERVAL) * m_fFPSTime);
		m_iFrames = 0;
		m_fFPSTime = TO_REAL(0.0);
	}
}

}

/* EOF */

