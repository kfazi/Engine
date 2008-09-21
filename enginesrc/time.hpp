#ifndef ENGINE_TIME_HPP
#define ENGINE_TIME_HPP

#include "config.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace engine
{

class CTime
{
	private:
		static boost::posix_time::ptime m_cLastTime;
		static real m_fFrameTime;
		static real m_fTotalTime;
		static real m_fFPSTime;
		static real m_fFPS;
		static int m_iFrames;
		CTime()
		{
		}
		~CTime()
		{
		}

	public:
		inline static real GetFPS()
		{
			return m_fFPS;
		}
		inline static int GetIntegerFPS()
		{
			return static_cast<unsigned int>(m_fFPS);
		}
		inline static real GetFrameTime()
		{
			return m_fFrameTime;
		}
		inline static real GetTotalTime()
		{
			return m_fTotalTime;
		}
		static void Update();
};

}

#endif /* ENGINE_TIME_HPP */

