#ifndef ENGINE_LOGGER_HPP
#define ENGINE_LOGGER_HPP

#include "common.hpp"
#include <map>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "string.hpp"

namespace engine
{

/**
 * Class encapsulating all logging functions.
 * Use it through CCore singleton.
 */
class DLLEXPORTIMPORT CLogger
{
	/** Allow CCore to create this class. */
	friend class CCore;
	friend void ::Create(CEngineMain &cEngineMain, int iArgc, char **pArgv);

	public:
		/**
		 * Type of logged message.
		 */
		enum EMessageType
		{
			DEBUG, /**< Debug type. */
			NOTIFY, /**< Notify type - the most common one, it informs about object creation, scene change, etc. */
			WARNING, /**< Warning type - used for example when some problems with sound occurred. */
			ERROR, /**< Error type - something went wrong, but there's a chance to recover. */
			SYSTEMERROR /**< System error type - engine will shutdown. */
		};

	private:
		/** Map of functors called when new message arrives. */
		std::map<unsigned int, boost::function<void (const CString &, const EMessageType)> > m_cFunctorMap;

		/** Next ID to assign when new logging function is registered. */
		unsigned int m_iNextId;

		boost::mutex cMutex;

		/** Default constructor. */
		CLogger()
		{
			m_iNextId = 0;
		}

		/** Destructor. */
		~CLogger()
		{
		}

		/**
		 * Generates next ID for registering logging function.
		 *
		 * @return Next ID.
		 */
		unsigned int GetNextId()
		{
			unsigned int iNextId = m_iNextId;
			while (m_cFunctorMap.find(iNextId) != m_cFunctorMap.end()) /* Make sure this ID isn't in use. */
				++iNextId;
			m_iNextId = iNextId + 1;
			return iNextId;
		}

	public:
		/**
		 * Registers new logging function.
		 *
		 * @param[in] cClass A pointer to the class instance, containing registered function.
		 * @param[in] pFunction A pointer to the registered function, returning void and taking const CString &, const CLogger::EMessageType arguments.
		 * @return ID of registered function.
		 */
		template <class CClass> unsigned int Register(CClass *cClass, void (CClass::*pFunction)(const CString &, const EMessageType))
		{
			unsigned int iId = GetNextId();
			m_cFunctorMap.insert(std::make_pair(iId, boost::bind(pFunction, cClass, _1, _2)));
			return iId;
		}

		/**
		 * Unregisters logging function with given ID.
		 *
		 * @param[in] iId ID of function to unregister.
		 * @return True, when function was successfully unregistered. False otherwise.
		 */
		bool Unregister(const unsigned int iId)
		{
			std::map<unsigned int, boost::function<void (const CString &, const EMessageType)> >::iterator cFoundFunctor = m_cFunctorMap.find(iId);
			if (cFoundFunctor == m_cFunctorMap.end())
				return false;
			m_cFunctorMap.erase(cFoundFunctor);
			return true;
		}

		/**
		 * Logs a message.
		 *
		 * @param[in] cMessage A message to log.
		 * @param[in] eMessageType Type of a message.
		 */
		void Log(const CString &cMessage, const EMessageType eMessageType = NOTIFY)
		{
			boost::mutex::scoped_lock mylock(cMutex, boost::defer_lock);
			mylock.lock();
			for (std::map<unsigned int, boost::function<void (const CString &, const EMessageType)> >::iterator cFunctorIterator = m_cFunctorMap.begin(); cFunctorIterator != m_cFunctorMap.end(); ++cFunctorIterator)
				(*cFunctorIterator).second(cMessage, eMessageType);
			mylock.unlock();
		}
};

}

#endif /* ENGINE_LOGGER_HPP */

/* EOF */

