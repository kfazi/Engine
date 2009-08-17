#ifndef ENGINE_LOGGER_HPP
#define ENGINE_LOGGER_HPP

#include "common.hpp"
#include <vector>
#include <queue>
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
	friend void ::CreateEngine(CEngineMain &cEngineMain, int iArgc, char **pArgv);

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
		struct SFunctorData
		{
			boost::function<void (const CString &, const EMessageType)> pFunctor;
			bool bRemoved;
			SFunctorData(boost::function<void (const CString &, const EMessageType)> pFunctor)
			{
				this->pFunctor = pFunctor;
				bRemoved = false;
			}
			SFunctorData()
			{
				bRemoved = true;
			}
		};

		/** Vector of registered functors called when new message arrives. */
		std::vector<SFunctorData> m_cRegisteredFunctors;

		/** Unregistered functors indices. */
		std::queue<unsigned int> m_cUnregisteredFunctorsIndices;

		/** Mutex for logging synchronization. */
		boost::mutex cMutex;

		/** Default constructor. */
		CLogger(unsigned int iAllocationBase = 5)
		{
			m_cRegisteredFunctors.resize(iAllocationBase, SFunctorData());
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
			if (m_cUnregisteredFunctorsIndices.size() > 0)
			{
				unsigned int iNextId = m_cUnregisteredFunctorsIndices.front();
				m_cUnregisteredFunctorsIndices.pop();
				return iNextId;
			}
			return m_cRegisteredFunctors.size();
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
			if (m_cRegisteredFunctors.size() <= iId)
				m_cRegisteredFunctors.resize(m_cRegisteredFunctors.size() * 2 + 1, SFunctorData());
			m_cRegisteredFunctors[iId] = SFunctorData(boost::bind(pFunction, cClass, _1, _2));
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
			if (iId >= m_cRegisteredFunctors.size() || m_cRegisteredFunctors[iId].bRemoved)
				return false;
			m_cRegisteredFunctors[iId].bRemoved = true;
			m_cUnregisteredFunctorsIndices.push(iId);
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
			for (std::vector<SFunctorData>::iterator cFunctorIterator = m_cRegisteredFunctors.begin(); cFunctorIterator != m_cRegisteredFunctors.end(); ++cFunctorIterator)
			{
				if (!(*cFunctorIterator).bRemoved)
				(*cFunctorIterator).pFunctor(cMessage, eMessageType);
			}
			mylock.unlock();
		}
};

}

#endif /* ENGINE_LOGGER_HPP */

/* EOF */

