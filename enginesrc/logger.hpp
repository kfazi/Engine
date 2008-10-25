#ifndef ENGINE_LOGGER_HPP
#define ENGINE_LOGGER_HPP

#include "engine.hpp"
#include <map>
#include <string>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

/**
 * Class encapsulating all logging functions.
 * Use it through CEngine singleton.
 */
class CLogger
{
	/** Allow CEngine to create this class. */
	friend class CEngine;

	public:
		/**
		 * Type of logged message.
		 */
		enum EMessageType
		{
			DEBUG, /**< Debug type - lowest priority. */
			NOTIFY, /**< Notify type - the most common one, it informs about object creation, scene change, etc. */
			WARNING, /**< Warning type - high priority, used for example when occured some problems with sound. */
			ERROR /**< Error type - highest priority, shutdowns engine. */
		};

	private:
		/** Map of functors called when new message arrives. */
		std::map<unsigned int, boost::function<void (const std::string &, const EMessageType)> > m_cFunctorMap;

		/** Next ID to assign when new logging function is registered. */
		unsigned int m_iNextId;

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
		 * Generates next ID for registrating logging function.
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
		 * Registrates new logging function.
		 *
		 * @param[in] cClass A pointer to the class instance, containing registrated function.
		 * @param[in] pFunction A pointer to the registrated function, returning void and taking const std::string &, const CLogger::EMessageType arguments.
		 * @return ID of registered function.
		 */
		template <class CClass> unsigned int Register(CClass *cClass, void (CClass::*pFunction)(const std::string &, const EMessageType))
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
			std::map<unsigned int, boost::function<void (const std::string &, const EMessageType)> >::iterator cFoundFunctor = m_cFunctorMap.find(iId);
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
		void Log(const std::string &cMessage, const EMessageType eMessageType = NOTIFY)
		{
			for (std::map<unsigned int, boost::function<void (const std::string &, const EMessageType)> >::iterator cFunctorIterator = m_cFunctorMap.begin(); cFunctorIterator != m_cFunctorMap.end(); ++cFunctorIterator)
				(*cFunctorIterator).second(cMessage, eMessageType);
			if (eMessageType == ERROR)
				CEngine::GetInstance()->Finish();
		}
};

}

#endif /* ENGINE_LOGGER_HPP */

/* EOF */

