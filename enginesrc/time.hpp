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
		static double m_fFrameTime;
		static double m_fTotalTime;
		static double m_fFPSTime;
		static double m_fFPS;
		static int m_iFrames;
		CTime()
		{
		}
		~CTime()
		{
		}

	public:
		inline static double GetFPS()
		{
			return m_fFPS;
		}
		inline static int GetIntegerFPS()
		{
			return static_cast<unsigned int>(m_fFPS);
		}
		inline static double GetFrameTime()
		{
			return m_fFrameTime;
		}
		inline static double GetTotalTime()
		{
			return m_fTotalTime;
		}
		static void Update();
};

}

#endif /* ENGINE_TIME_HPP */

