#ifndef ENGINE_PAD_HPP
#define ENGINE_PAD_HPP

#include <vector>
#include "SystemInputController.hpp"

namespace engine
{

class CPad: public CSystemInputController<CPad, int>
{
	friend class CSystemInput;

	public:
		class CPov
		{
			friend class CSystemInput;

			public:
				enum EDirection
				{
					Centered,
					North,
					South,
					East,
					West,
					NorthEast,
					SouthEast,
					NorthWest,
					SouthWest
				};

			private:
				EDirection m_eDirection;

				void SetDirection(const EDirection eDirection)
				{
					m_eDirection = eDirection;
				}

			public:
				EDirection GetDirection() const
				{
					return m_eDirection;
				}
		};

		class CSlider
		{
			friend class CSystemInput;

			private:
				bool bX;
		};

		enum EButton
		{
			PrimaryButton,
			SecondaryButton
		};

	private:
		std::vector<EState> m_cButtonsState;
		std::vector<CVector3> m_cAxes;
		std::vector<CPov> m_cPOVs;
		std::vector<CSlider> m_cSliders;
		std::vector<CVector3> m_cVectors;

		CPad(const int iButtonsQuantity, const int iAxesQuantity, const int iPOVsQuantity, const int iSlidersQuantity, const int iVectorsQuantity)
		{
			m_cButtonsState.reserve(iButtonsQuantity);
			m_cAxes.reserve(iAxesQuantity);
			m_cPOVs.reserve(iPOVsQuantity);
			m_cSliders.reserve(iSlidersQuantity);
			m_cVectors.reserve(iVectorsQuantity);
		}

		void SetButtonState(const EState eState, const unsigned int iButtonNumber)
		{
			m_cButtonsState[iButtonNumber] = eState;
		}

		void SetAxisPosition(const CVector3 &cPosition, const int iAxisNumber)
		{
			m_cAxes[iAxisNumber] = cPosition;
		}

	public:
		EState GetButtonState(const unsigned int iButtonNumber) const
		{
			return m_cButtonsState[iButtonNumber];
		}

		const CVector3 &GetAxisPosition(const int iAxisNumber) const
		{
			return m_cAxes[iAxisNumber];
		}
};

}

#endif /* ENGINE_PAD_HPP */

/* EOF */
