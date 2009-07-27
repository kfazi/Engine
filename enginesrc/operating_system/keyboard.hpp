#ifndef ENGINE_KEYBOARD_HPP
#define ENGINE_KEYBOARD_HPP

#include <vector>
#include "SystemInputController.hpp"

namespace engine
{

class DLLEXPORTIMPORT CKeyboard: public CSystemInputController<CKeyboard, int>
{
	friend class CSystemInput;

	public:
		enum EKey
		{
			Unassigned,
			Escape,
			ExclamationMark,
			At,
			Hash,
			Dollar,
			Percent,
			Caret, /* ^ */
			Ampersand,
			Star,
			LeftParenthesis,
			RightParenthesis,
			Minus,
			Equals,
			Backspace,
			Tab,
			Q,
			W,
			E,
			R,
			T,
			Y,
			U,
			I,
			O,
			P,
			LeftBracket,
			RightBracket,
			Return,
			LeftCtrl,
			A,
			S,
			D,
			F,
			G,
			H,
			J,
			K,
			L,
			Semicolon,
			Apostrophe,
			Grave, /* Accent. */
			LeftShift,
			Backslash,
			Z,
			X,
			C,
			V,
			B,
			N,
			M,
			Comma,
			Dot,
			Slash,
			RightShift,
			NumStar,
			LeftAlt,
			SpaceBar,
			CapsLock,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			NumLock,
			ScrollLock,
			Num7,
			Num8,
			Num9,
			NumMinus,
			Num4,
			Num5,
			Num6,
			NumPlus,
			Num1,
			Num2,
			Num3,
			Num0,
			NumDot,
			Oem102,
			F11,
			F12,
			F13, /* NEC PC98. */
			F14, /* NEC PC98. */
			F15, /* NEC PC98. */
			Kana, /* Japanese keyboard. */
			AbntC1, /* Portugese keyboard. */
			Convert, /* Japanese keyboard. */
			NoConvert, /* Japanese keyboard. */
			Yen, /* Japanese keyboard. */
			AbntC2, /* Portugese keyboard. */
			NumEquals, /* NEC PC98. */
			PrevTrack,
			NecAt, /* NEC PC98. */
			Colon, /* NEC PC98. */
			Underline, /* NEC PC98. */
			Kanji, /* Japanese keyboard. */
			Stop, /* NEC PC98. */
			Ax, /* Japan AX. */
			Unlabeled, /* J3100. */
			NextTrack,
			NumReturn,
			RightCtrl,
			Mute,
			Calculator,
			PlayPause,
			MediaStop,
			VolumeDown,
			VolumeUp,
			WebHome,
			NumComma, /* NEC PC98. */
			NumSlash,
			SysRq,
			RightAlt,
			Pause,
			Home,
			Up,
			PageUp,
			Left,
			Right,
			End,
			Down,
			PageDown,
			Insert,
			Delete,
			LeftWin,
			RightWin,
			Apps,
			Power,
			Sleep,
			Wake,
			WebSearch,
			WebFavorites,
			WebRefresh,
			WebStop,
			WebForward,
			WebBack,
			MyComputer,
			Mail,
			MediaSelect
		};

	private:
		static const int s_iKeysQuantity;
		std::vector<EState> m_cKeysState;

		CKeyboard()
		{
			m_cKeysState.reserve(s_iKeysQuantity);
		}

		void SetKeyState(const EState eState, const unsigned int iKeyNumber)
		{
			m_cKeysState[iKeyNumber] = eState;
		}

	public:
		EState GetKeyState(const unsigned int iKeyNumber) const
		{
			return m_cKeysState[iKeyNumber];
		}

		CString KeyToString(const EKey eKey) const;

		CString KeyNameToString(const EKey eKey) const;
};

}

#endif /* ENGINE_KEYBOARD_HPP */

/* EOF */
