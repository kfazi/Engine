#ifndef ENGINE_TIME_HPP
#define ENGINE_TIME_HPP

#include "common.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace engine
{

/**
 * Class for storing frames time.
 * This class is static.
 */
class DLLEXPORTIMPORT CTime
{
	/** Allow CCore to call Update(). */
	friend class CCore;

	private:
		/** Last frame time. */
		static boost::posix_time::ptime m_cLastTime;

		/** How much time generation of last frame took. */
		static double m_fFrameTime;

		/** Overall time of running engine. */
		static double m_fTotalTime;

		/** Time for calculating FPS. */
		static double m_fFPSTime;

		/** Amount of frames per second (FPS). */
		static double m_fFPS;

		/** Frames counter. */
		static int m_iFrames;

		/** Private constructor - this class is static, and can't be created. */
		CTime()
		{
		}

		/** Private destructor - this class is static, and can't be destroyed. */
		~CTime()
		{
		}

		/**
		 * @internal
		 * Updates all time data.
		 * Can be called only by CCore.
		 */
		static void Update();

	public:
		/**
		 * @return Current real frames per second.
		 */
		inline static double GetFPS()
		{
			return m_fFPS;
		}

		/**
		 * @return Current frames per second as an integer.
		 */
		inline static int GetIntegerFPS()
		{
			return static_cast<unsigned int>(m_fFPS);
		}

		/**
		 * @return Time of last frame.
		 */
		inline static double GetFrameTime()
		{
			return m_fFrameTime;
		}

		/**
		 * Total time of running engine.
		 */
		inline static double GetTotalTime()
		{
			return m_fTotalTime;
		}
};

}

#endif /* ENGINE_TIME_HPP */

