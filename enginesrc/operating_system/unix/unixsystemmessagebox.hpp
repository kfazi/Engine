#ifdef UNIX

#ifndef ENGINE_UNIX_SYSTEM_MESSAGEBOX_HPP
#define ENGINE_UNIX_SYSTEM_MESSAGEBOX_HPP

#include <vector>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include "../../common.hpp"

namespace engine
{

class CUnixSystemMessageBox
{
	private:
		Display *m_pDisplay;

		Window m_sWindow;

		XVisualInfo *m_pVisualInfo;

		Atom m_aProtocols[2];

	public:
		CUnixSystemMessageBox();
		~CUnixSystemMessageBox();
};

}

#endif /* ENGINE_UNIX_SYSTEM_WINDOW_HPP */

#endif /* UNIX */

/* EOF */

