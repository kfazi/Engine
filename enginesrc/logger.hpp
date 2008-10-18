#ifndef ENGINE_LOGGER_HPP
#define ENGINE_LOGGER_HPP

#include "engine.hpp"
#include "functor.hpp"
#include <vector>
#include <string>
#include <boost/format.hpp>

namespace engine
{

class CLogger
{
	/* Allow engine to create this class. */
	friend class CEngine;

	public:
		enum EMessageType
		{
			DEBUG,
			NOTIFY,
			WARNING,
			ERROR
		};
	private:
		CLogger()
		{
		}

		~CLogger()
		{
			for (std::vector<CFunctor2Base<void, const std::string &, const EMessageType> *>::iterator cFunctorIterator = m_cFunctorVector.begin(); cFunctorIterator != m_cFunctorVector.end(); ++cFunctorIterator)
				delete (*cFunctorIterator);
		}

		template <class CClass> class CSpecificFunctor: public CFunctor2<CClass, void, const std::string &, const EMessageType>
		{
			public:
				CSpecificFunctor(CClass *pClass, void (CClass::*pFunction)(const std::string &sMessage, const EMessageType eMessageType)): CFunctor2<CClass, void, const std::string &, const EMessageType>(pClass, pFunction)
				{
				}
		};
		std::vector<CFunctor2Base<void, const std::string &, const EMessageType> *> m_cFunctorVector;
	public:
		template<class CClass> void Register(CClass *cClass, void (CClass::*pFunction)(const std::string &, const EMessageType))
		{
			m_cFunctorVector.push_back(new CSpecificFunctor<CClass>(cClass, pFunction));
		}
		template<class CClass> bool Unregister(CClass *cClass, void (CClass::*pFunction)(const std::string &, const EMessageType))
		{
			for (std::vector<CFunctor2Base<void, const std::string &, const EMessageType> *>::iterator cFunctorIterator = m_cFunctorVector.begin(); cFunctorIterator != m_cFunctorVector.end(); ++cFunctorIterator)
			{
//				if (*cFunctorIterator == CFunctor2<CClass, void, const std::string &, const EMessageType>(cClass, pFunction))
				{
					/* Function address match */
					delete (*cFunctorIterator);
					m_cFunctorVector.erase(cFunctorIterator);
					return true;
				}
			}
			return false;
		}
		inline void Log(const std::string &cMessage, const EMessageType eMessageType = NOTIFY)
		{
			for (std::vector<CFunctor2Base<void, const std::string &, const EMessageType> *>::iterator cFunctorIterator = m_cFunctorVector.begin(); cFunctorIterator != m_cFunctorVector.end(); ++cFunctorIterator)
				(*cFunctorIterator)->Call(cMessage, eMessageType);
			if (eMessageType == ERROR)
				exit(-1);
		}
};

}

#endif /* ENGINE_LOGGER_HPP */

/* EOF */

