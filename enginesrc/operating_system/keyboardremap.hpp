/* All values here are taken from <OISKeyboard.h>. */

private:
	inline int GetLastKey()
	{
		return 0xED;
	}

public:
	enum EKey
	{
		Unassigned = OIS::KC_UNASSIGNED,
		Escape = OIS::KC_ESCAPE,
		ExclamationMark = OIS::KC_1,
		At = OIS::KC_2,
		Hash = OIS::KC_3,
		Dollar = OIS::KC_4,
		Percent = OIS::KC_5,
		Caret = OIS::KC_6, /* ^ */
		Ampersand = OIS::KC_7,
		Star = OIS::KC_8,
		LeftParenthesis = OIS::KC_9,
		RightParenthesis = OIS::KC_0,
		Minus = OIS::KC_MINUS,
		Equals = OIS::KC_EQUALS,
		Backspace = OIS::KC_BACK,
		Tab = OIS::KC_TAB,
		Q = OIS::KC_Q,
		W = OIS::KC_W,
		E = OIS::KC_E,
		R = OIS::KC_R,
		T = OIS::KC_T,
		Y = OIS::KC_Y,
		U = OIS::KC_U,
		I = OIS::KC_I,
		O = OIS::KC_O,
		P = OIS::KC_P,
		LeftBracket = OIS::KC_LBRACKET,
		RightBracket = OIS::KC_RBRACKET,
		Return = OIS::KC_RETURN,
		LeftCtrl = OIS::KC_LCONTROL,
		A = OIS::KC_A,
		S = OIS::KC_S,
		D = OIS::KC_D,
		F = OIS::KC_F,
		G = OIS::KC_G,
		H = OIS::KC_H,
		J = OIS::KC_J,
		K = OIS::KC_K,
		L = OIS::KC_L,
		Semicolon = OIS::KC_SEMICOLON,
		Apostrophe = OIS::KC_APOSTROPHE,
		Grave = OIS::KC_GRAVE, /* Accent. */
		LeftShift = OIS::KC_LSHIFT,
		Backslash = OIS::KC_BACKSLASH,
		Z = OIS::KC_Z,
		X = OIS::KC_X,
		C = OIS::KC_C,
		V = OIS::KC_V,
		B = OIS::KC_B,
		N = OIS::KC_N,
		M = OIS::KC_M,
		Comma = OIS::KC_COMMA,
		Dot = OIS::KC_PERIOD,
		Slash = OIS::KC_SLASH,
		RightShift = OIS::KC_RSHIFT,
		NumStar = OIS::KC_MULTIPLY,
		LeftAlt = OIS::KC_LMENU,
		SpaceBar = OIS::KC_SPACE,
		Capital = OIS::KC_CAPITAL, /* Caps lock :? */
		F1 = OIS::KC_F1,
		F2 = OIS::KC_F2,
		F3 = OIS::KC_F3,
		F4 = OIS::KC_F4,
		F5 = OIS::KC_F5,
		F6 = OIS::KC_F6,
		F7 = OIS::KC_F7,
		F8 = OIS::KC_F8,
		F9 = OIS::KC_F9,
		F10 = OIS::KC_F10,
		NumLock = OIS::KC_NUMLOCK,
		ScrollLock = OIS::KC_SCROLL,
		Num7 = OIS::KC_NUMPAD7,
		Num8 = OIS::KC_NUMPAD8,
		Num9 = OIS::KC_NUMPAD9,
		NumMinus = OIS::KC_SUBTRACT,
		Num4 = OIS::KC_NUMPAD4,
		Num5 = OIS::KC_NUMPAD5,
		Num6 = OIS::KC_NUMPAD6,
		NumPlus = OIS::KC_ADD,
		Num1 = OIS::KC_NUMPAD1,
		Num2 = OIS::KC_NUMPAD2,
		Num3 = OIS::KC_NUMPAD3,
		Num0 = OIS::KC_NUMPAD0,
		NumDot = OIS::KC_DECIMAL,
		Oem102 = OIS::KC_OEM_102,
		F11 = OIS::KC_F11,
		F12 = OIS::KC_F12,
		F13 = OIS::KC_F13, /* NEC PC98. */
		F14 = OIS::KC_F14, /* NEC PC98. */
		F15 = OIS::KC_F15, /* NEC PC98. */
		Kana = OIS::KC_KANA, /* Japanese keyboard. */
		AbntC1 = OIS::KC_ABNT_C1, // Portugese keyboard. */
		Convert = OIS::KC_CONVERT, /* Japanese keyboard. */
		NoConvert = OIS::KC_NOCONVERT, /* Japanese keyboard. */
		Yen = OIS::KC_YEN, /* Japanese keyboard. */
		AbntC2 = OIS::KC_ABNT_C2, /* Portugese keyboard. */
		NumEquals = OIS::KC_NUMPADEQUALS, /* NEC PC98. */
		PrevTrack = OIS::KC_PREVTRACK,
		NecAt = OIS::KC_AT, /* NEC PC98. */
		Colon = OIS::KC_COLON, /* NEC PC98. */
		Underline = OIS::KC_UNDERLINE, /* NEC PC98. */
		Kanji = OIS::KC_KANJI, /* Japanese keyboard. */
		Stop = OIS::KC_STOP, /* NEC PC98. */
		Ax = OIS::KC_AX, /* Japan AX. */
		Unlabeled = OIS::KC_UNLABELED, /* J3100. */
		NextTrack = OIS::KC_NEXTTRACK,
		NumReturn = OIS::KC_NUMPADENTER,
		RightCtrl = OIS::KC_RCONTROL,
		Mute = OIS::KC_MUTE,
		Calculator = OIS::KC_CALCULATOR,
		PlayPause = OIS::KC_PLAYPAUSE,
		MediaStop = OIS::KC_MEDIASTOP,
		VolumeDown = OIS::KC_VOLUMEDOWN,
		VolumeUp = OIS::KC_VOLUMEUP,
		WebHome = OIS::KC_WEBHOME,
		NumComma = OIS::KC_NUMPADCOMMA, /* NEC PC98. */
		NumSlash = OIS::KC_DIVIDE,
		SysRq = OIS::KC_SYSRQ,
		RightAlt = OIS::KC_RMENU,
		Pause = OIS::KC_PAUSE,
		Home = OIS::KC_HOME,
		Up = OIS::KC_UP,
		PageUp = OIS::KC_PGUP,
		Left = OIS::KC_LEFT,
		Right = OIS::KC_RIGHT,
		End = OIS::KC_END,
		Down = OIS::KC_DOWN,
		PageDown = OIS::KC_PGDOWN,
		Insert = OIS::KC_INSERT,
		Delete = OIS::KC_DELETE,
		LeftWin = OIS::KC_LWIN,
		RightWin = OIS::KC_RWIN,
		Apps = OIS::KC_APPS,
		Power = OIS::KC_POWER,
		Sleep = OIS::KC_SLEEP,
		Wake = OIS::KC_WAKE,
		WebSearch = OIS::KC_WEBSEARCH,
		WebFavorites = OIS::KC_WEBFAVORITES,
		WebRefresh = OIS::KC_WEBREFRESH,
		WebStop = OIS::KC_WEBSTOP,
		WebForward = OIS::KC_WEBFORWARD,
		WebBack = OIS::KC_WEBBACK,
		MyComputer = OIS::KC_MYCOMPUTER,
		Mail = OIS::KC_MAIL,
		MediaSelect = OIS::KC_MEDIASELECT
	};

/* EOF */

