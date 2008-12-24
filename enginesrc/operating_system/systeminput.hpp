#ifndef ENGINE_SYSTEM_INPUT_HPP
#define ENGINE_SYSTEM_INPUT_HPP

#include "../common.hpp"
#include <list>
#include <map>
#include <vector>
#include <OISInputManager.h>
#include <OISException.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>
#include <OISEvents.h>
#include "../math/vector3.hpp"
#include "../useful.hpp"

namespace engine
{

class CSystemInput: public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
{
	friend class CCore;

#include "keyboardremap.hpp"

	public:
		enum EState
		{
			Pressed,
			Released
		};

		enum EMouseButton
		{
			MouseLeftButton = OIS::MB_Left,
			MouseRightButton = OIS::MB_Right,
			MouseMiddleButton = OIS::MB_Middle,
			MouseButton3 = OIS::MB_Button3,
			MouseButton4 = OIS::MB_Button4,
			MouseButton5 = OIS::MB_Button5,
			MouseButton6 = OIS::MB_Button6,
			MouseButton7 = OIS::MB_Button7
		};

		class CMouseEvent
		{
			private:
				EMouseButton m_eButton;
				CVector3 m_cPosition;
				bool m_bIsMoving;
			public:
				CMouseEvent(const CVector3 &cPosition)
				{
					m_cPosition = cPosition;
					m_bIsMoving = true;
				}
				CMouseEvent(const CVector3 &cPosition, const EMouseButton eButton)
				{
					m_cPosition = cPosition;
					m_eButton = eButton;
					m_bIsMoving = false;
				}
				bool IsMoving() const
				{
					return m_bIsMoving;
				}
				const CVector3 &GetPosition() const
				{
					return m_cPosition;
				}
				EMouseButton GetButtonState() const
				{
					return m_eButton;
				}
		};

	private:
		class CKeyboardFunctor
		{
			private:
				EKey m_eKey;
				const OIS::Object *m_pDevice;
				boost::function<void (const EKey eKey, const EState eAction)> m_pFunctor;

			public:
				CKeyboardFunctor()
				{
				}

				CKeyboardFunctor(const boost::function<void (const EKey eKey, const EState eAction)> pFunctor, const OIS::Object *pDevice, const EKey eKey)
				{
					m_eKey = eKey;
					m_pDevice = pDevice;
					m_pFunctor = pFunctor;
				}

				inline const OIS::Object *GetDevice() const
				{
					return m_pDevice;
				}

				inline EKey GetKey() const
				{
					return m_eKey;
				}

				inline void Call(const EKey eKey, const EState eKeyState)
				{
					m_pFunctor(eKey, eKeyState);
				}
		};

		std::map<unsigned int, CKeyboardFunctor> m_cKeyboardFunctorMap;

		bool keyPressed(const OIS::KeyEvent &sEvent)
		{
			for (std::map<unsigned int, CKeyboardFunctor>::iterator cFunctorIterator = m_cKeyboardFunctorMap.begin(); cFunctorIterator != m_cKeyboardFunctorMap.end(); ++cFunctorIterator)
			{
				CKeyboardFunctor *pFunctor = &(*cFunctorIterator).second;
				if (pFunctor->GetDevice() == sEvent.device && (pFunctor->GetKey() == static_cast<EKey>(sEvent.key) || pFunctor->GetKey() == Unassigned))
					pFunctor->Call(static_cast<EKey>(sEvent.key), Pressed);
			}
			return true;
		}

		bool keyReleased(const OIS::KeyEvent &sEvent)
		{
			for (std::map<unsigned int, CKeyboardFunctor>::iterator cFunctorIterator = m_cKeyboardFunctorMap.begin(); cFunctorIterator != m_cKeyboardFunctorMap.end(); ++cFunctorIterator)
			{
				CKeyboardFunctor *pFunctor = &(*cFunctorIterator).second;
				if (pFunctor->GetDevice() == sEvent.device && (pFunctor->GetKey() == static_cast<EKey>(sEvent.key) || pFunctor->GetKey() == Unassigned))
					pFunctor->Call(static_cast<EKey>(sEvent.key), Released);
			}
			return true;
		}

		bool mouseMoved(const OIS::MouseEvent &sEvent)
		{
			return true;
		}

		bool mousePressed(const OIS::MouseEvent &sEvent, OIS::MouseButtonID eId)
		{
			return true;
		}

		bool mouseReleased(const OIS::MouseEvent &sEvent, OIS::MouseButtonID eId)
		{
			return true;
		}

		bool buttonPressed(const OIS::JoyStickEvent &arg, int button)
		{
			return true;
		}

		bool buttonReleased(const OIS::JoyStickEvent &arg, int button)
		{
			return true;
		}

		bool axisMoved(const OIS::JoyStickEvent &arg, int axis)
		{
			return true;
		}

		//Joystick Event, amd sliderID
		bool sliderMoved(const OIS::JoyStickEvent &, int)
		{
			return true;
		}

		//Joystick Event, amd povID
		bool povMoved(const OIS::JoyStickEvent &, int)
		{
			return true;
		}

		OIS::InputManager *m_pOISInputSystem;

		std::vector<OIS::Keyboard *> cKeyboardVector;
		std::vector<OIS::Mouse *> cMouseVector;
		std::vector<OIS::JoyStick *> cControllerVector;

		unsigned int m_iNextKeyboardId;
		unsigned int m_iNextMouseId;
		unsigned int m_iNextControllerId;

		unsigned int GetNextKeyboardId()
		{
			/* TODO: ADD CRITICAL SECTION START */
			return m_iNextKeyboardId++;
			/* TODO: ADD CRITICAL SECTION END */
		}

		unsigned int GetNextMouseId()
		{
			/* TODO: ADD CRITICAL SECTION START */
			return m_iNextMouseId++;
			/* TODO: ADD CRITICAL SECTION END */
		}

		unsigned int GetNextControllerId()
		{
			/* TODO: ADD CRITICAL SECTION START */
			return m_iNextControllerId++;
			/* TODO: ADD CRITICAL SECTION END */
		}

	protected:
		CSystemInput()
		{
			m_iNextKeyboardId = 0;
			m_iNextMouseId = 0;
			m_iNextControllerId = 0;
			OIS::ParamList cOISParamList;
			GetOISParamList(cOISParamList);
			m_pOISInputSystem = OIS::InputManager::createInputSystem(cOISParamList);
			/* Create keyboards. */
			for (int i = 0; i < m_pOISInputSystem->numKeyBoards(); ++i)
			{
				try
				{
					OIS::Keyboard *pKeyboard = static_cast<OIS::Keyboard *>(m_pOISInputSystem->createInputObject(OIS::OISKeyboard, true));
					pKeyboard->setEventCallback(this);
					cKeyboardVector.push_back(pKeyboard);
				}
				catch (...)
				{
					/* Missing device isn't critical - just show warning. */
					Warning(Format("Can't create keyboard number %1%") % i);
				}
			}
			/* Create mice. */
			for (int i = 0; i < m_pOISInputSystem->numMice(); ++i)
			{
				try
				{
					OIS::Mouse *pMouse = static_cast<OIS::Mouse *>(m_pOISInputSystem->createInputObject(OIS::OISMouse, true));
					pMouse->setEventCallback(this);
					cMouseVector.push_back(pMouse);
				}
				catch (...)
				{
					/* Missing device isn't critical - just show warning. */
					Warning(Format("Can't create mouse number %1%") % i);
				}
			}
			/* Create other devices. */
			for (int i = 0; i < m_pOISInputSystem->numJoysticks(); ++i)
			{
				try
				{
					OIS::JoyStick *pController = static_cast<OIS::JoyStick *>(m_pOISInputSystem->createInputObject(OIS::OISJoyStick, true));
					pController->setEventCallback(this);
					cControllerVector.push_back(pController);
				}
				catch (...)
				{
					/* Missing device isn't critical - just show warning. */
					Warning(Format("Can't create game controller device number %1%") % i);
				}
			}
		}

		virtual ~CSystemInput()
		{
		}

		virtual void GetOISParamList(OIS::ParamList &cOISParamList)
		{
		}

	public:
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
};

}

#endif /* ENGINE_SYSTEM_INPUT_HPP */

/* EOF */

