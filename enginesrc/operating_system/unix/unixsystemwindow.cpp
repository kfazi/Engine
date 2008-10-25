#include "unixsystemwindow.hpp"
#include "../../engine.hpp"
#include "../../useful.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

namespace engine
{

Bool CUnixSystemWindow::WaitForMapNotify(Display *pDisplay, XEvent *pEvent, char *pArgument)
{
	return (pEvent->type == MapNotify) && (pEvent->xmap.window == reinterpret_cast<Window>(pArgument));
}

CUnixSystemWindow::CUnixSystemWindow(const std::string cDisplayName): CSystemWindow()
{
	if (cDisplayName == "")
		m_pDisplay = XOpenDisplay(NULL);
	else
		m_pDisplay = XOpenDisplay(cDisplayName.c_str());
	if (!m_pDisplay)
		Error(Format("Couldn't open display %1%!") % cDisplayName);
	BuildAllResolutionsSet();
	UpdateDesktopResolution();
	m_iCurrentResolution = m_iDesktopResolution;
	m_sWindow = static_cast<Window>(0);
	m_pVisualInfo = NULL;
	m_sGLContext = static_cast<GLXContext>(0);
}

CUnixSystemWindow::~CUnixSystemWindow()
{
	DestroyWindow();
	if (m_iCurrentResolution != m_iDesktopResolution)
		SetScreenResolution(m_iDesktopResolution);
	XCloseDisplay(m_pDisplay);
}

void CUnixSystemWindow::SwapBuffers()
{
	if (!m_sWindow)
		return;
	glXSwapBuffers(m_pDisplay, m_sWindow);
}

bool CUnixSystemWindow::SetScreenResolution(const unsigned int iResolutionNumber)
{
	if (iResolutionNumber >= m_cUnixResolutionsVector.size())
		Error(Format("CUnixSystemWindow::GetResolution(%1%) - resolution number out of bounds!") % iResolutionNumber);
	/* Get our screen. */
	int iScreen = DefaultScreen(m_pDisplay);
	/* Unlock mode switch. */
	XF86VidModeLockModeSwitch(m_pDisplay, iScreen, 0);
	if (!XF86VidModeSwitchToMode(m_pDisplay, iScreen, m_cUnixResolutionsVector[iResolutionNumber].pModeInfo))
	{
		/* Lock mode switch and exit with failure. */
		XF86VidModeLockModeSwitch(m_pDisplay, iScreen, 1);
		return false;
	}
	/* Set viewport position to top-left corner. */
	XF86VidModeSetViewPort(m_pDisplay, iScreen, 0, 0);
	/* Lock mode switch. */
	XF86VidModeLockModeSwitch(m_pDisplay, iScreen, 1);
	m_iCurrentResolution = iResolutionNumber;
	return true;
}

XVisualInfo *CUnixSystemWindow::ChooseBestVisual(const unsigned int iResolutionNumber)
{
	CResolution *pResolution = &m_cUnixResolutionsVector[iResolutionNumber].cResolution;
	/* Get list of visuals for our screen and display. */
	XVisualInfo *pVisualInfoList;
	XVisualInfo sDummy;
	int iVisualCount;
	sDummy.screen = DefaultScreen(m_pDisplay);
	pVisualInfoList = XGetVisualInfo(m_pDisplay, VisualScreenMask, &sDummy, &iVisualCount);
	if (!pVisualInfoList)
		return NULL;
	int iBestVisual = -1;
	unsigned int iBestColorDifference = 0xFFFFFFFF;
	unsigned int iBestOtherDifference = 0xFFFFFFFF;
	int iRequestedRed;
	int iRequestedGreen;
	int iRequestedBlue;
	switch (pResolution->iBpp)
	{
		case 15:
			iRequestedRed = 5;
			iRequestedGreen = 5;
			iRequestedBlue = 5;
			break;
		case 16:
			iRequestedRed = 5;
			iRequestedGreen = 6;
			iRequestedBlue = 5;
		default:
			iRequestedRed = 8;
			iRequestedGreen = 8;
			iRequestedBlue = 8;
	}
	for (int i = 0; i < iVisualCount; ++i)
	{
		/* We want GL, RGBA & DOUBLEBUFFER. */
		int iGL;
		int iRGBA;
		int iDoubleBuffer;
		glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_USE_GL, &iGL);
		glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_RGBA, &iRGBA);
		glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_DOUBLEBUFFER, &iDoubleBuffer);
		if (iGL && iRGBA && iDoubleBuffer)
		{
			int iRed;
			int iGreen;
			int iBlue;
			int iAlpha;
			int iDepth;
			int iStencil;
			int iAccumRed;
			int iAccumGreen;
			int iAccumBlue;
			int iAccumAlpha;
			/* Get visual parameters. */
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_RED_SIZE, &iRed);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_GREEN_SIZE, &iGreen);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_BLUE_SIZE, &iBlue);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_ALPHA_SIZE, &iAlpha);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_DEPTH_SIZE, &iDepth);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_STENCIL_SIZE, &iStencil);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_ACCUM_RED_SIZE, &iAccumRed);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_ACCUM_GREEN_SIZE, &iAccumGreen);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_ACCUM_BLUE_SIZE, &iAccumBlue);
			glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_ACCUM_ALPHA_SIZE, &iAccumAlpha);
			int iAccum = (iAccumRed > 0 || iAccumGreen > 0 || iAccumBlue > 0 || iAccumAlpha > 0);
			if (!iAlpha || !iDepth || !iStencil || !iAccum)
				continue;
			/* Calculate differences. */
			unsigned int iColorDifference = (iRequestedRed - iRed) * (iRequestedRed - iRed) + (iRequestedGreen - iGreen) * (iRequestedGreen - iGreen) + (iRequestedBlue - iBlue) * (iRequestedBlue - iBlue);
			unsigned int iOtherDifference = (OPENGL_ALPHA - iAlpha) * (OPENGL_ALPHA - iAlpha) + (OPENGL_DEPTH - iDepth) * (OPENGL_DEPTH - iDepth) + (OPENGL_STENCIL - iStencil) * (OPENGL_STENCIL - iStencil) + (iRequestedRed - iAccumRed) * (iRequestedRed - iAccumRed) + (iRequestedGreen - iAccumGreen) * (iRequestedGreen - iAccumGreen) + (iRequestedBlue - iAccumBlue) * (iRequestedBlue - iAccumBlue) + (OPENGL_ALPHA - iAccumAlpha) * (OPENGL_ALPHA - iAccumAlpha);
			/* Select best match. */
			if ((iColorDifference < iBestColorDifference) || (iColorDifference == iBestColorDifference && iOtherDifference < iBestOtherDifference))
			{
				iBestColorDifference = iColorDifference;
				iBestOtherDifference = iOtherDifference;
				iBestVisual = i;
			}
		}
	}
	XVisualInfo *pResult = NULL;
	if (iBestVisual >= 0)
		pResult = XGetVisualInfo(m_pDisplay, VisualIDMask, &pVisualInfoList[iBestVisual], &iVisualCount);
	XFree(pVisualInfoList);
	return pResult;
}

void CUnixSystemWindow::CreateWindow(const unsigned int iResolutionNumber, char *pCaption, const bool bFullScreen)
{
	if (iResolutionNumber >= m_cUnixResolutionsVector.size())
		Error(Format("CUnixSystemWindow::CreateWindow(%1%, ...) - resolution number out of bounds!") % iResolutionNumber);
	CResolution *pResolution = &m_cUnixResolutionsVector[iResolutionNumber].cResolution;
	Debug(Format("Creating window: %1%x%2%, %3%bpp @ %4%Hz, fullscreen: %5%") % pResolution->iWidth % pResolution->iHeight % static_cast<int>(pResolution->iBpp) % pResolution->iRefreshRate % ((bFullScreen) ? "true" : "false"));
	/* Choose visual. */
	m_pVisualInfo = ChooseBestVisual(iResolutionNumber);
	if (!m_pVisualInfo)
		Error(Format("CUnixSystemWindow::CreateWindow(%1%, ...) - Can't get visual info!") % iResolutionNumber);
	/* Create OpenGL context */
	m_sGLContext = glXCreateContext(m_pDisplay, m_pVisualInfo, NULL, GL_TRUE);
	if (!m_sGLContext)
		Error(Format("CUnixSystemWindow::CreateWindow(%1%, ...) - Can't create OpenGL visual context!") % iResolutionNumber);
	/* Create color map. */
	Colormap sColormap = XCreateColormap(m_pDisplay, RootWindow(m_pDisplay, m_pVisualInfo->screen), m_pVisualInfo->visual, AllocNone);
	/* Set window attributes. */
	XSetWindowAttributes m_sWindowAttributes;
	m_sWindowAttributes.colormap = sColormap;
	m_sWindowAttributes.border_pixel = 0;
	m_sWindowAttributes.event_mask = StructureNotifyMask | ExposureMask | FocusChangeMask | VisibilityChangeMask;
	m_sWindow = XCreateWindow(m_pDisplay, RootWindow(m_pDisplay, m_pVisualInfo->screen), 0, 0, pResolution->iWidth, pResolution->iHeight, 0, OPENGL_DEPTH, InputOutput, m_pVisualInfo->visual, CWBorderPixel | CWColormap | CWEventMask, &m_sWindowAttributes);
	if (!m_sWindow)
		Error(Format("CUnixSystemWindow::CreateWindow(%1%, ...) - Can't create window!") % iResolutionNumber);
	/* Set window min/max size. */
	XSizeHints *pSizeHints = XAllocSizeHints();
	if (!pSizeHints)
		Error(Format("CUnixSystemWindow::CreateWindow(%1%, ...) - Can't create size hints!") % iResolutionNumber);
	pSizeHints->flags = PSize | PMinSize | PMaxSize;
	pSizeHints->min_width = pResolution->iWidth;
	pSizeHints->base_width = pResolution->iWidth;
	pSizeHints->max_width = pResolution->iWidth;
	pSizeHints->min_height = pResolution->iHeight;
	pSizeHints->base_height = pResolution->iHeight;
	pSizeHints->max_height = pResolution->iHeight;
	XSetWMNormalHints(m_pDisplay, m_sWindow, pSizeHints);
	XFree(pSizeHints);
	/* Set window caption. */
	XTextProperty sWindowCaptionProperty;
	if (!XStringListToTextProperty(&pCaption, 1, &sWindowCaptionProperty))
		Error(Format("CUnixSystemWindow::CreateWindow(%1%, ...) - Can't create window caption!") % iResolutionNumber);
	XSetWMName(m_pDisplay, m_sWindow, &sWindowCaptionProperty);
	/* Get the delete window WM protocol atom. */
	m_aProtocols[WM_DELETE_WINDOW] = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", False);
	/* Get the ping WM protocol atom. */
	m_aProtocols[WM_PING] = XInternAtom(m_pDisplay, "_NET_WM_PING", False);
	/* Allow us to trap window protocols. */
	XSetWMProtocols(m_pDisplay, m_sWindow, m_aProtocols, 2);
	XMapWindow(m_pDisplay, m_sWindow);
	/* Wait for map notification. */
	XEvent sEvent;
	XIfEvent(m_pDisplay, &sEvent, WaitForMapNotify, reinterpret_cast<char *>(m_sWindow));
	/* Make sure that our window ends up on top of things. */
	XRaiseWindow(m_pDisplay, m_sWindow);
	XFlush(m_pDisplay);
	/* Select current OpenGL context. */
	glXMakeCurrent(m_pDisplay, m_sWindow, m_sGLContext);
}

void CUnixSystemWindow::DestroyWindow()
{
	if (m_sGLContext)
	{
		/* Unset OpenGL Context. */
		glXMakeCurrent(m_pDisplay, None, NULL);
		/* Delete the context. */
		glXDestroyContext(m_pDisplay, m_sGLContext);
		m_sGLContext = static_cast<GLXContext>(0);
	}
	if (m_sWindow)
	{
		/* Unmap the window. */
		XUnmapWindow(m_pDisplay, m_sWindow);
		/* Destroy the window. */
		XDestroyWindow(m_pDisplay, m_sWindow);
		m_sWindow = static_cast<Window>(0);
	}
	XFree(m_pVisualInfo);
	m_pVisualInfo = NULL;
}

void CUnixSystemWindow::ProcessEvents()
{
	if (!m_pVisualInfo)
		return;
	/* Synchronize display events. */
	XSync(m_pDisplay, False);
	/* Process whole event queue. */
	while (XPending(m_pDisplay))
	{
		XEvent sEvent;
		/* Pull next event from event queue. */
		XNextEvent(m_pDisplay, &sEvent);
		switch (sEvent.type)
		{
			/* Was the window closed by the window manager? */
			case ClientMessage:
			{
				if (static_cast<Atom>(sEvent.xclient.data.l[0]) == m_aProtocols[WM_DELETE_WINDOW])
				{
					if (!m_pOnCloseFunctor || !m_pOnCloseFunctor())
						CEngine::GetInstance()->Finish();
				}
				else if (static_cast<Atom>(sEvent.xclient.data.l[0]) == m_aProtocols[WM_PING])
				{
					sEvent.xclient.window = RootWindow(m_pDisplay, m_pVisualInfo->screen);
					XSendEvent(m_pDisplay, RootWindow(m_pDisplay, m_pVisualInfo->screen), False, SubstructureNotifyMask | SubstructureRedirectMask, &sEvent);
				}
				break;
			}
			/* Was the window activated? */
			case FocusIn:
				break;
			/* Was the window de-activated? */
			case FocusOut:
				break;
			/* Was the window destroyed? */
			case DestroyNotify:
				break;
			default:
				break;
		}
	}
}

void CUnixSystemWindow::BuildAllResolutionsSet()
{
	/* Clear old data. */
	m_cUnixResolutionsVector.clear();
	/* Get our screen. */
	int iScreen = DefaultScreen(m_pDisplay);

	XVisualInfo sDummy;
	int iVisualCount;
	/* Acquire visual info. */
	XVisualInfo *pVisualInfoList = XGetVisualInfo(m_pDisplay, 0, &sDummy, &iVisualCount);
	if (!pVisualInfoList)
		return;
	/* Build RGB array. */
	std::vector<int> cRGBVector;
	for (int i = 0; i < iVisualCount; ++i)
	{
		int iGL;
		int iRGBA;
		glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_USE_GL, &iGL);
		glXGetConfig(m_pDisplay, &pVisualInfoList[i], GLX_RGBA, &iRGBA);
		if (iGL && iRGBA)
			cRGBVector.push_back((pVisualInfoList[i].depth > 24) ? 24 : pVisualInfoList[i].depth); /* Add depth to the vector. Cut values above 24 BPP. */
	}
	XFree(pVisualInfoList);

	/* Build resolutions array. */
	int iModeCount;
	XF86VidModeModeInfo **pModeList;
	XF86VidModeGetAllModeLines(m_pDisplay, iScreen, &iModeCount, &pModeList);
	for (int i = 0; i < iModeCount; ++i)
	{
		for (std::vector<int>::iterator cRGBIterator = cRGBVector.begin(); cRGBIterator != cRGBVector.end(); ++cRGBIterator)
		{
			CUnixResolution cUnixResolution;
			cUnixResolution.cResolution = CResolution(pModeList[i]->hdisplay, pModeList[i]->vdisplay, (pModeList[i]->vsyncend - pModeList[i]->vsyncstart) * 10, *cRGBIterator);
			cUnixResolution.pModeInfo = pModeList[i];
			/* Make sure there is no duplicates. */
			bool bDuplicate = false;
			for (std::vector<CUnixResolution>::iterator cUnixResolutionsIterator = m_cUnixResolutionsVector.begin(); cUnixResolutionsIterator != m_cUnixResolutionsVector.end(); ++cUnixResolutionsIterator)
			{
				if (*cUnixResolutionsIterator == cUnixResolution)
				{
					bDuplicate = true;
					break;
				}
			}
			if (!bDuplicate)
				m_cUnixResolutionsVector.push_back(cUnixResolution);
		}
	}
	XFree(pModeList);

	/* Sort results. */
	std::sort(m_cUnixResolutionsVector.begin(), m_cUnixResolutionsVector.end());
}

void CUnixSystemWindow::UpdateDesktopResolution()
{
	/* Get our screen. */
	int iScreen = DefaultScreen(m_pDisplay);
	/* Get desktop depth. */
	int iBpp = DefaultDepth(m_pDisplay, iScreen);
	int iModeCount;
	XF86VidModeModeInfo **pModeList;
	XF86VidModeGetAllModeLines(m_pDisplay, iScreen, &iModeCount, &pModeList);
	/* The first mode in the list is the desktop mode. */
	CResolution cResolution(pModeList[0]->hdisplay, pModeList[0]->vdisplay, (pModeList[0]->vsyncend - pModeList[0]->vsyncstart) * 10, iBpp);
	/* Search for desktop mode in our vector. */
	for (unsigned int i = 0; i < m_cUnixResolutionsVector.size(); ++i)
	{
		if (m_cUnixResolutionsVector[i].cResolution == cResolution)
		{
			m_iDesktopResolution = i;
			break;
		}
	}
	XFree(pModeList);
}

const CSystemWindow::CResolution *CUnixSystemWindow::GetResolution(const unsigned int iResolutionNumber) const
{
	if (iResolutionNumber >= m_cUnixResolutionsVector.size())
		Error(Format("CUnixSystemWindow::GetResolution(%1%) - resolution number out of bounds!") % iResolutionNumber);
	return &m_cUnixResolutionsVector[iResolutionNumber].cResolution;
}

unsigned int CUnixSystemWindow::GetResolutionsCount() const
{
	return m_cUnixResolutionsVector.size();
}

void CUnixSystemWindow::MessageBox(const std::string &cCaption, const std::string &cMessage) const
{
	/* TODO: ADD MESSAGEBOX :P */
	std::cout << cCaption << ": " << cMessage << std::endl;
}

}

/* EOF */

