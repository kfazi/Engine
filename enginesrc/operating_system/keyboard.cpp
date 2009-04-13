#include "../common.hpp"
#include "../useful.hpp"
#include "keyboard.hpp"

namespace engine
{

const int CKeyboard::s_iKeysQuantity = CKeyboard::MediaSelect + 1;

CString CKeyboard::KeyToString(const EKey eKey) const
{
	switch (eKey)
	{
		case ExclamationMark: return "!";
		case At: return "@";
		case Hash: return "#";
		case Dollar: return "$";
		case Percent: return "%";
		case Caret: return "^";
		case Ampersand: return "&";
		case Star: return "*";
		case LeftParenthesis: return "(";
		case RightParenthesis: return ")";
		case Minus: return "-";
		case Equals: return "=";
		case Tab: return "\t";
		case Q: return "Q";
		case W: return "W";
		case E: return "E";
		case R: return "R";
		case T: return "T";
		case Y: return "Y";
		case U: return "U";
		case I: return "I";
		case O: return "O";
		case P: return "P";
		case LeftBracket: return "[";
		case RightBracket: return "]";
		case A: return "A";
		case S: return "S";
		case D: return "D";
		case F: return "F";
		case G: return "G";
		case H: return "H";
		case J: return "J";
		case K: return "K";
		case L: return "L";
		case Semicolon: return ";";
		case Apostrophe: return "'";
		case Grave: return "`";
		case Backslash: return "\\";
		case Z: return "Z";
		case X: return "X";
		case C: return "C";
		case V: return "V";
		case B: return "B";
		case N: return "N";
		case M: return "M";
		case Comma: return ",";
		case Dot: return ".";
		case Slash: return "/";
		case NumStar: return "*";
		case SpaceBar: return " ";
		case Num7: return "7";
		case Num8: return "8";
		case Num9: return "9";
		case NumMinus: return "-";
		case Num4: return "4";
		case Num5: return "5";
		case Num6: return "6";
		case NumPlus: return "+";
		case Num1: return "1";
		case Num2: return "2";
		case Num3: return "3";
		case Num0: return "0";
		case NumDot: return ".";
		case NumEquals: return "=";
		case NecAt: return "@";
		case Colon: return ";";
		case Underline: return "_";
		case NumComma: return ",";
		case NumSlash: return "/";

		case Escape:
		case Backspace:
		case Return:
		case LeftCtrl:
		case LeftShift:
		case RightShift:
		case LeftAlt:
		case CapsLock:
		case F1:
		case F2:
		case F3:
		case F4:
		case F5:
		case F6:
		case F7:
		case F8:
		case F9:
		case F10:
		case NumLock:
		case ScrollLock:
		case Oem102:
		case F11:
		case F12:
		case F13:
		case F14:
		case F15:
		case Kana:
		case AbntC1:
		case Convert:
		case NoConvert:
		case Yen:
		case AbntC2:
		case PrevTrack:
		case Kanji:
		case Stop:
		case Ax:
		case Unlabeled:
		case NextTrack:
		case NumReturn:
		case RightCtrl:
		case Mute:
		case Calculator:
		case PlayPause:
		case MediaStop:
		case VolumeDown:
		case VolumeUp:
		case WebHome:
		case SysRq:
		case RightAlt:
		case Pause:
		case Home:
		case Up:
		case PageUp:
		case Left:
		case Right:
		case End:
		case Down:
		case PageDown:
		case Insert:
		case Delete:
		case LeftWin:
		case RightWin:
		case Apps:
		case Power:
		case Sleep:
		case Wake:
		case WebSearch:
		case WebFavorites:
		case WebRefresh:
		case WebStop:
		case WebForward:
		case WebBack:
		case MyComputer:
		case Mail:
		case MediaSelect:
		case Unassigned:
			Error(Format("CSystemInput::KeyToString - Can't translate key %1% to string") % eKey);
			return ""; /* Dummy return. */
		default:
			Error(Format("CSystemInput::KeyToString - Unknown key %1%") % eKey);
			return ""; /* Dummy return. */
	}
}

CString CKeyboard::KeyNameToString(const EKey eKey) const
{
	switch (eKey)
	{
		case Escape: return "Escape";
		case ExclamationMark: return "!";
		case At: return "@";
		case Hash: return "#";
		case Dollar: return "$";
		case Percent: return "%";
		case Caret: return "^";
		case Ampersand: return "&";
		case Star: return "*";
		case LeftParenthesis: return "(";
		case RightParenthesis: return ")";
		case Minus: return "-";
		case Equals: return "=";
		case Backspace: return "Backspace";
		case Tab: return "Tab";
		case Q: return "Q";
		case W: return "W";
		case E: return "E";
		case R: return "R";
		case T: return "T";
		case Y: return "Y";
		case U: return "U";
		case I: return "I";
		case O: return "O";
		case P: return "P";
		case LeftBracket: return "[";
		case RightBracket: return "]";
		case Return: return "Return";
		case LeftCtrl: return "LeftCtrl";
		case A: return "A";
		case S: return "S";
		case D: return "D";
		case F: return "F";
		case G: return "G";
		case H: return "H";
		case J: return "J";
		case K: return "K";
		case L: return "L";
		case Semicolon: return ";";
		case Apostrophe: return "'";
		case Grave: return "`";
		case LeftShift: return "LeftShift";
		case Backslash: return "\\";
		case Z: return "Z";
		case X: return "X";
		case C: return "C";
		case V: return "V";
		case B: return "B";
		case N: return "N";
		case M: return "M";
		case Comma: return ",";
		case Dot: return ".";
		case Slash: return "/";
		case RightShift: return "RightShift";
		case NumStar: return "*";
		case LeftAlt: return "LeftAlt";
		case SpaceBar: return " ";
		case CapsLock: return "CapsLock";
		case F1: return "F1";
		case F2: return "F2";
		case F3: return "F3";
		case F4: return "F4";
		case F5: return "F5";
		case F6: return "F6";
		case F7: return "F7";
		case F8: return "F8";
		case F9: return "F9";
		case F10: return "F10";
		case NumLock: return "NumLock";
		case ScrollLock: return "ScrollLock";
		case Num7: return "7";
		case Num8: return "8";
		case Num9: return "9";
		case NumMinus: return "-";
		case Num4: return "4";
		case Num5: return "5";
		case Num6: return "6";
		case NumPlus: return "+";
		case Num1: return "1";
		case Num2: return "2";
		case Num3: return "3";
		case Num0: return "0";
		case NumDot: return ".";
		case Oem102: return "Oem102";
		case F11: return "F11";
		case F12: return "F12";
		case F13: return "F13";
		case F14: return "F14";
		case F15: return "F15";
		case Kana: return "Kana";
		case AbntC1: return "AbntC1";
		case Convert: return "Convert";
		case NoConvert: return "NoConvert";
		case Yen: return "Yen";
		case AbntC2: return "AbntC2";
		case NumEquals: return "=";
		case PrevTrack: return "PrevTrack";
		case NecAt: return "@";
		case Colon: return ";";
		case Underline: return "_";
		case Kanji: return "Kanji";
		case Stop: return "Stop";
		case Ax: return "Ax";
		case Unlabeled: return "Unlabeled";
		case NextTrack: return "NextTrack";
		case NumReturn: return "NumReturn";
		case RightCtrl: return "RightCtrl";
		case Mute: return "Mute";
		case Calculator: return "Calculator";
		case PlayPause: return "PlayPause";
		case MediaStop: return "MediaStop";
		case VolumeDown: return "VolumeDown";
		case VolumeUp: return "VolumeUp";
		case WebHome: return "WebHome";
		case NumComma: return ",";
		case NumSlash: return "/";
		case SysRq: return "SysRq";
		case RightAlt: return "RightAlt";
		case Pause: return "Pause";
		case Home: return "Home";
		case Up: return "Up";
		case PageUp: return "PageUp";
		case Left: return "Left";
		case Right: return "Right";
		case End: return "End";
		case Down: return "Down";
		case PageDown: return "PageDown";
		case Insert: return "Insert";
		case Delete: return "Delete";
		case LeftWin: return "LeftWin";
		case RightWin: return "RightWin";
		case Apps: return "Apps";
		case Power: return "Power";
		case Sleep: return "Sleep";
		case Wake: return "Wake";
		case WebSearch: return "WebSearch";
		case WebFavorites: return "WebFavorites";
		case WebRefresh: return "WebRefresh";
		case WebStop: return "WebStop";
		case WebForward: return "WebForward";
		case WebBack: return "WebBack";
		case MyComputer: return "MyComputer";
		case Mail: return "Mail";
		case MediaSelect: return "MediaSelect";
		case Unassigned:
			Error(Format("CSystemInput::KeyNameToString - Can't translate unassigned key to string"));
			return ""; /* Dummy return. */
		default:
			Error(Format("CSystemInput::KeyNameToString - Unknown key %1%") % eKey);
			return ""; /* Dummy return. */
	}
}

}

/* EOF */
