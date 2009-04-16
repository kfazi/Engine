#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

#include "common.hpp"
#include "string.hpp"
#include <boost/format.hpp>

extern int main(int argc, char **argv);

namespace engine
{

class CSceneManager;
class CFunctionManager;
class CSystemDirectories;
class CSystemWindow;
class CSystemInfo;
class CLogger;
class CConfig;
class CEngineMain;

/**
 * Main engine class.
 * This is singleton.
 * Use it to communicate with the engine.
 */
class CCore
{
	friend class CEngineMain;
	friend void Debug(const CString &cMessage);
	friend void Debug(const boost::basic_format<TChar> &cFormat);

	private:
		CSceneManager *m_pSceneManager; /**< Pointer to the scene manager. */
		CFunctionManager *m_pFunctionManager; /**< Pointer to the function manager. */
		CSystemDirectories *m_pSystemDirectories; /**< Pointer to the system directories object. */
		CSystemWindow *m_pSystemWindow; /**< Pointer to the system window object. */
		CSystemInfo *m_pSystemInfo; /**< Pointer to the system info object. */
		CLogger *m_pLogger; /**< Pointer to the logger system. */
		CConfig *m_pConfig; /**< Pointer to the config system. */
		double m_fFrameTime; /**< How much time passed in last frame. */
		bool m_bFinished;
		static bool m_bDebug;
		static CCore *m_pEngine; /**< Makes sure CCore is created before main(). */

		/**
		 * Private constructor.
		 */
		CCore();

		/**
		 * Private destructor.
		 */
		~CCore();

		static void Create(CCore *pEngine, const CString &cConfigFile);

	public:
		/**
		 * @return Instance of the engine.
		 */
		inline static CCore *GetInstance()
		{
			return m_pEngine;
		}

		/**
		 * @return Pointer to the scene manager object.
		 */
		inline CSceneManager *GetSceneManager()
		{
			return m_pSceneManager;
		}

		/**
		 * @return Pointer to the function manager object.
		 */
		inline CFunctionManager *GetFunctionManager()
		{
			return m_pFunctionManager;
		}

		/**
		 * @return Pointer to the system directories object.
		 */
		inline CSystemDirectories *GetSystemDirectories()
		{
			return m_pSystemDirectories;
		}

		/**
		 * @return Pointer to the system window object.
		 */
		inline CSystemWindow *GetWindow()
		{
			return m_pSystemWindow;
		}

		/**
		 * @return Pointer to the system info object.
		 */
		inline CSystemInfo *GetSystemInfo()
		{
			return m_pSystemInfo;
		}

		/**
		 * @return Pointer to the logger system object.
		 */
		inline CLogger *GetLogger()
		{
			return m_pLogger;
		}

		/**
		 * @return Pointer to the config system object.
		 */
		inline CConfig *GetConfig()
		{
			return m_pConfig;
		}

		inline bool Finished() const
		{
			return m_bFinished;
		}

		inline void Finish()
		{
			m_bFinished = true;
		}

		/**
		 * Convert CCore to a string.
		 * Creates string with all engine objects converted to a string.
		 * @return A string.
		 */
		CString ToString() const
		{
			return "CCore[ ";// + m_pSceneManager->ToString() + " ]";
		}

		/**
		 * Processes next frame.
		 */
		void ProcessFrame();
};

}

#endif /* ENGINE_CORE_HPP */

/* EOF */
