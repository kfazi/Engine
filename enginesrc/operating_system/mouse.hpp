#ifndef ENGINE_MOUSE_HPP
#define ENGINE_MOUSE_HPP

#include <vector>
#include "SystemInputController.hpp"

namespace engine
{

class CMouse: public CSystemInputController<CMouse, int>
{
	friend class CSystemInput;

	public:
		enum EButton
		{
			LeftButton,
			RightButton,
			MiddleButton
		};

	private:
		std::vector<EState> m_cButtonsState;

		CVector3 m_cPosition;

		CMouse(const int iButtonsQuantity)
		{
			m_cButtonsState.reserve(iButtonsQuantity);
		}

		void SetButtonState(const EState eState, const unsigned int iButtonNumber)
		{
			m_cButtonsState[iButtonNumber] = eState;
		}

		void SetPosition(const CVector3 &cPosition)
		{
			m_cPosition = cPosition;
		}

	public:
		EState GetButtonState(const unsigned int iButtonNumber) const
		{
			return m_cButtonsState[iButtonNumber];
		}

		const CVector3 &GetPosition() const
		{
			return m_cPosition;
		}
};

}

#endif /* ENGINE_MOUSE_HPP */

/* EOF */
