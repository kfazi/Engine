#ifndef ENGINE_SYSTEM_WINDOW_HPP
#define ENGINE_SYSTEM_WINDOW_HPP

#include "../common.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

class CSystemWindow
{
	friend class CCore;

	public:
		class CResolution
		{
			private:
				unsigned int m_iWidth;
				unsigned int m_iHeight;
				unsigned short m_iRefreshRate;
				unsigned char m_iBpp;
			public:
				CResolution()
				{
				}
				CResolution(const unsigned int iWidth, const unsigned int iHeight, const unsigned short iRefreshRate, const unsigned char iBpp)
				{
					m_iWidth = iWidth;
					m_iHeight = iHeight;
					m_iRefreshRate = iRefreshRate;
					m_iBpp = iBpp;
				}
				inline unsigned int GetWidth() const
				{
					return m_iWidth;
				}
				inline unsigned int GetHeight() const
				{
					return m_iHeight;
				}
				inline unsigned short GetRefreshRate() const
				{
					return m_iRefreshRate;
				}
				inline unsigned char GetBitsPerPixel() const
				{
					return m_iBpp;
				}
				bool operator < (const CResolution &cResolution) const
				{
					return ((m_iWidth * m_iHeight) < (cResolution.m_iWidth * cResolution.m_iHeight)) || (m_iBpp < cResolution.m_iBpp) || (m_iRefreshRate < cResolution.m_iRefreshRate);
				}
				bool operator == (const CResolution &cResolution) const
				{
					return (m_iWidth == cResolution.m_iWidth) && (m_iHeight == cResolution.m_iHeight) && (m_iBpp == cResolution.m_iBpp) && (m_iRefreshRate == cResolution.m_iRefreshRate);
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

//		virtual void CreateWindow(const unsigned int iResolutionNumber, char *pCaption, const bool bFullScreen) = 0;

		virtual void DestroyWindow() = 0;

		virtual void ProcessEvents() = 0;

	public:
		virtual const CResolution *GetResolution(const unsigned int iResolutionNumber) const = 0;

		virtual unsigned int GetResolutionsCount() const = 0;

		virtual const std::string &GetDriverName() const = 0;

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
//				CreateWindow(iResolutionNumber, "Temporary Tweak!", bFullScreen);
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

