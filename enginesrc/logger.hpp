#ifndef ENGINE_LOGGER_HPP
#define ENGINE_LOGGER_HPP

#include "engine.hpp"
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
			for (std::vector<CFunctor *>::iterator cFunctorIterator = m_cFunctorVector.begin(); cFunctorIterator != m_cFunctorVector.end(); ++cFunctorIterator)
				delete (*cFunctorIterator);
		}

		class CFunctor
		{
			public:
				void *m_pClass;
				virtual ~CFunctor()
				{
				}
				virtual void Call(const std::string &sMessage, const EMessageType eMessageType) = 0;
		};
		template <class CClass> class CSpecificFunctor: public CFunctor
		{
			public:
				void (CClass::*m_pFunction)(const std::string &, const EMessageType);
				CSpecificFunctor(CClass *pClass, void (CClass::*pFunction)(const std::string &sMessage, const EMessageType eMessageType))
				{
					m_pClass = pClass;
					m_pFunction = pFunction;
				}
				virtual void Call(const std::string &sMessage, const EMessageType eMessageType)
				{
					(*(static_cast<CClass *>(m_pClass)).*m_pFunction)(sMessage, eMessageType);
				}
		};
		std::vector<CFunctor *> m_cFunctorVector;
	public:
		template<class CClass> void Register(CClass *cClass, void (CClass::*pFunction)(const std::string &, const EMessageType))
		{
			m_cFunctorVector.push_back(new CSpecificFunctor<CClass>(cClass, pFunction));
		}
		template<class CClass> bool Unregister(CClass *cClass, void (CClass::*pFunction)(const std::string &, const EMessageType))
		{
			for (std::vector<CFunctor *>::iterator cFunctorIterator = m_cFunctorVector.begin(); cFunctorIterator != m_cFunctorVector.end(); ++cFunctorIterator)
			{
				if ((*cFunctorIterator)->m_pClass == cClass)
				{
					/* It is the same class instance */
					if ((static_cast<CSpecificFunctor<CClass> *>(*cFunctorIterator))->m_pFunction == pFunction)
					{
						/* Function address match */
						delete (*cFunctorIterator);
						m_cFunctorVector.erase(cFunctorIterator);
						return true;
					}
				}
			}
			return false;
		}
		inline void Log(const std::string &cMessage, const EMessageType eMessageType = NOTIFY)
		{
			for (std::vector<CFunctor *>::iterator cFunctorIterator = m_cFunctorVector.begin(); cFunctorIterator != m_cFunctorVector.end(); ++cFunctorIterator)
				(*cFunctorIterator)->Call(cMessage, eMessageType);
			if (eMessageType == ERROR)
				exit(-1);
		}
};

}

#endif /* ENGINE_LOGGER_HPP */

/* EOF */

