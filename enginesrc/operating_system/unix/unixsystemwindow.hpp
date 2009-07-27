#ifdef UNIX

#ifndef ENGINE_UNIX_SYSTEM_WINDOW_HPP
#define ENGINE_UNIX_SYSTEM_WINDOW_HPP

#include <vector>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include "../../common.hpp"
#include "../systemwindow.hpp"

namespace engine
{

class DLLEXPORTIMPORT CUnixSystemWindow: public CSystemWindow
{
	friend class CCore;
	private:
		class CUnixResolution
		{
			public:
				CResolution cResolution;
				XF86VidModeModeInfo *pModeInfo;
				bool operator < (const CUnixResolution &cUnixResolution) const
				{
					return cResolution < cUnixResolution.cResolution;
				}
				bool operator == (const CUnixResolution &cUnixResolution) const
				{
					return (cResolution == cUnixResolution.cResolution) && (pModeInfo == cUnixResolution.pModeInfo);
				}
		};
		enum
		{
			WM_DELETE_WINDOW,
			WM_PING
		};

		std::vector<CUnixResolution> m_cUnixResolutionsVector;

		CString m_cDriverName;

		Display *m_pDisplay;

		Window m_sWindow;

		GLXContext m_sGLContext;

		XVisualInfo *m_pVisualInfo;

		Atom m_aProtocols[2];

		CUnixSystemWindow(const CString cDisplayName = "");

		static Bool WaitForMapNotify(Display *pDisplay, XEvent *pEvent, char *pArgument);

		virtual ~CUnixSystemWindow();

		virtual void SwapBuffers();

		virtual bool SetScreenResolution(const unsigned int iResolutionNumber);

		virtual void CreateWindow(const unsigned int iResolutionNumber, char *pCaption, const bool bFullScreen);

		virtual void DestroyWindow();

		virtual void ProcessEvents();

		XVisualInfo *ChooseBestVisual(const unsigned int iResolutionNumber);

		void BuildAllResolutionsSet();

		void UpdateDesktopResolution();

	public:
		virtual const CResolution *GetResolution(const unsigned int iResolutionNumber) const;

		virtual unsigned int GetResolutionsCount() const;

		virtual const CString &GetDriverName() const;

		virtual void MessageBox(const CString &cCaption, const CString &cMessage) const;
};

}

#endif /* ENGINE_UNIX_SYSTEM_WINDOW_HPP */

#endif /* UNIX */

/* EOF */

