#ifndef ENGINE_SYSTEM_WINDOW_HPP
#define ENGINE_SYSTEM_WINDOW_HPP

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

class CSystemWindow
{
	friend class CEngine;

	public:
		class CResolution
		{
			public:
				unsigned int iWidth;
				unsigned int iHeight;
				unsigned short iRefreshRate;
				unsigned char iBpp;
				CResolution()
				{
				}
				CResolution(const unsigned int iWidth, const unsigned int iHeight, const unsigned short iRefreshRate, const unsigned char iBpp)
				{
					this->iWidth = iWidth;
					this->iHeight = iHeight;
					this->iRefreshRate = iRefreshRate;
					this->iBpp = iBpp;
				}
				bool operator < (const CResolution &cResolution) const
				{
					return ((iWidth * iHeight) < (cResolution.iWidth * cResolution.iHeight)) || (iBpp < cResolution.iBpp) || (iRefreshRate < cResolution.iRefreshRate);
				}
				bool operator == (const CResolution &cResolution) const
				{
					return (iWidth == cResolution.iWidth) && (iHeight == cResolution.iHeight) && (iBpp == cResolution.iBpp) && (iRefreshRate == cResolution.iRefreshRate);
				}
				bool operator != (const CResolution &cResolution) const
				{
					return !(*this == cResolution);
				}
		};

	private:
		bool m_bWindowCreated;

	protected:
		unsigned int m_iDesktopResolution;
		unsigned int m_iCurrentResolution;
		boost::function<bool ()> m_pOnCloseFunctor;

		CSystemWindow()
		{
			m_iDesktopResolution = 0;
			m_iCurrentResolution = 0;
			m_bWindowCreated = false;
		}

		virtual ~CSystemWindow()
		{
		}

		virtual void SwapBuffers() = 0;

		virtual bool SetScreenResolution(const unsigned int iResolutionNumber) = 0;

		virtual void CreateWindow(const unsigned int iResolutionNumber, char *pCaption, const bool bFullScreen) = 0;

		virtual void DestroyWindow() = 0;

		virtual void ProcessEvents() = 0;

	public:
		virtual const CResolution *GetResolution(const unsigned int iResolutionNumber) const = 0;

		virtual unsigned int GetResolutionsCount() const = 0;

		virtual void MessageBox(const std::string &cCaption, const std::string &cMessage) const = 0;

		bool SetResolution(const unsigned int iResolutionNumber, const bool bFullScreen = true)
		{
			bool bMustRecreateWindow = false;
			if (iResolutionNumber != m_iCurrentResolution && bFullScreen)
			{
				if (!SetScreenResolution(iResolutionNumber))
					return false;
				bMustRecreateWindow = true;
			}
			if (bMustRecreateWindow || !m_bWindowCreated)
			{
				DestroyWindow();
				CreateWindow(iResolutionNumber, "Temporary Tweak!", bFullScreen);
				m_bWindowCreated = true;
			}
			return true;
		}

		template <class CClass> void SetOnCloseFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnCloseFunctor = boost::bind(pFunctor, cClass);
		}

		inline unsigned int GetCurrentResolutionNumber() const
		{
			return m_iCurrentResolution;
		}

		inline unsigned int GetDesktopResolutionNumber() const
		{
			return m_iDesktopResolution;
		}
};

}

#endif /* ENGINE_SYSTEM_WINDOW_HPP */

/* EOF */

