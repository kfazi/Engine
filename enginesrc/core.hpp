#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

#include "common.hpp"
#include "string.hpp"
#include <boost/format.hpp>


namespace engine
{

class CEngineMain;

}

/**
 * Creates engine's core.
 *
 * @param[in] cEngineMain Main class responsible for managing applications flow.
 * @param[in] iArgc Quantity of arguments passed to the application (the same as in main()).
 * @param[in] pArgv Two dimensional array of zero terminated arguments passed to the application (the same as in main()).
 */
extern "C" DLLEXPORTIMPORT void Create(engine::CEngineMain &cEngineMain, int iArgc, char **pArgv);

/**
 * Destroys engine's core.
 */
extern "C" DLLEXPORTIMPORT void Destroy();

namespace engine
{

class CSceneManager;
class CFunctionManager;
class CSystemDirectories;
class CSystemDisplayManager;
class CSystemWindow;
class CSystemModule;
class CSystemInfo;
class CLogger;
class CConfig;
class CRenderersManager;

/**
 * Main engine class.
 * This is singleton.
 * Use it to communicate with the engine.
 */
class DLLEXPORTIMPORT CCore
{
	friend void Debug(const CString &cMessage);
	friend void Debug(const boost::basic_format<TChar> &cFormat);
	friend void ::Create(CEngineMain &cEngineMain, int iArgc, char **pArgv);
	friend void ::Destroy();

	private:
		CEngineMain *m_pEngineMain; /**< Application's class. */
		CSceneManager *m_pSceneManager; /**< Pointer to the scene manager. */
		CFunctionManager *m_pFunctionManager; /**< Pointer to the function manager. */
		CSystemDirectories *m_pSystemDirectories; /**< Pointer to the system directories object. */
		CSystemDisplayManager *m_pSystemDisplayManager; /**< Pointer to the system display manager object. */
		CSystemWindow *m_pSystemWindow; /**< Pointer to the system window object. */
		CSystemModule *m_pSystemModule; /**< Pointer to the system module object. */
		CSystemInfo *m_pSystemInfo; /**< Pointer to the system info object. */
		CLogger *m_pLogger; /**< Pointer to the logger system. */
		CConfig *m_pConfig; /**< Pointer to the config system. */
		CRenderersManager *m_pRenderersManager; /**< Pointer to the renderers manager system. */
		double m_fFrameTime; /**< How much time passed in last frame. */
		bool m_bFinished; /**< Flag indicating if engine is going to return to operating system. */
		static CString s_cConfigFile; /**< Startup configuration file. */
		static CCore *s_pEngine; /**< Singleton's instance. */
		static bool s_bDebug; /**< Flag indicating if engine is in debug mode. */

		/**
		 * Private constructor.
		 */
		CCore();

		/**
		 * Private destructor.
		 */
		~CCore();

		/**
		 * Creates all core systems.
		 */
		void Create();

	public:
		/**
		 * @return Instance of the engine.
		 */
		inline static CCore *GetInstance()
		{
			return s_pEngine;
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
		* @return Pointer to the system display mnager object.
		*/
		inline CSystemDisplayManager *GetSystemDisplayManager()
		{
			return m_pSystemDisplayManager;
		}

		/**
		 * @return Pointer to the system window object.
		 */
		inline CSystemWindow *GetWindow()
		{
			return m_pSystemWindow;
		}

		/**
		 * @return Pointer to the system window object.
		 */
		inline CSystemModule *GetModule()
		{
			return m_pSystemModule;
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

		inline CRenderersManager *GetRenderersManager()
		{
			return m_pRenderersManager;
		}

		inline bool IsFinished() const
		{
			return m_bFinished;
		}

		inline void Finish()
		{
			m_bFinished = true;
		}

		/**
		 * Processes next frame.
		 */
		void ProcessFrame();
};

}

#endif /* ENGINE_CORE_HPP */

/* EOF */
