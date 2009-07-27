#ifndef ENGINE_SYSTEM_INPUT_HPP
#define ENGINE_SYSTEM_INPUT_HPP

#include "../common.hpp"
#include <list>
#include <map>
#include <vector>
#include "../math/vector3.hpp"
#include "../useful.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "pad.hpp"

namespace engine
{

class DLLEXPORTIMPORT CSystemInput
{
	friend class CCore;

	protected:
/*
		void KeyDown(const EKey eKey, const int iKeyboardNumber);
		void KeyUp(const EKey eKey, const int iKeyboardNumber);
		void MouseButtonDown(const int iButton, const int iMouseNumber);
		void MouseButtonUp(const int iButton, const int iMouseNumber);
		void MouseMove(const double fX, const double fY, const double fZ);
		void ControllerButtonDown(const int iButton, const int iControllerNumber);
		void ControllerButtonUp(const int iButton, const int iControllerNumber);
		void ControllerMove(const double fX, const double fY, const double fZ, const int iControllerNumber);
*/

	public:

/*
		template <class CClass> unsigned int RegisterKeyboardHandler(CClass *cClass, void (CClass::*pFunctor)(const EKey eKey, const EState eAction), const EKey eKey, const unsigned int iKeyboardNumber = 0)
		{
			if (iKeyboardNumber >= cKeyboardVector.size())
				Error("CSystemInput::RegisterKeyboardHandler - iKeyboardNumber is out of range");
			unsigned int iId = GetNextKeyboardId();
			m_cKeyboardFunctorMap.insert(std::make_pair(iId, CKeyboardFunctor(boost::bind(pFunctor, cClass, _1, _2), cKeyboardVector[iKeyboardNumber], eKey)));
			return iId;
		}

		template <class CClass> unsigned int RegisterKeyboardHandler(CClass *cClass, void (CClass::*pFunctor)(const EKey eKey, const EState eAction), const unsigned int iKeyboardNumber = 0)
		{
			return RegisterKeyboardHandler(cClass, pFunctor, Unassigned, iKeyboardNumber);
		}

		bool UnregisterKeyboardHandler(const unsigned int iId)
		{
			std::map<unsigned int, CKeyboardFunctor>::iterator cFoundFunctor = m_cKeyboardFunctorMap.find(iId);
			if (cFoundFunctor == m_cKeyboardFunctorMap.end())
				return false;
			m_cKeyboardFunctorMap.erase(cFoundFunctor);
			return true;
		}
*/
};

}

#endif /* ENGINE_SYSTEM_INPUT_HPP */

/* EOF */

