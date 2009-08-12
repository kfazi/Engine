#ifndef ENGINE_SYSTEM_WINDOW_HPP
#define ENGINE_SYSTEM_WINDOW_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

struct SSystemSpecificWindowData;

class DLLEXPORTIMPORT CSystemWindow
{
	friend class CSystemDisplay;

	private:
		boost::function<bool ()> m_pOnCloseFunctor;
		boost::function<bool ()> m_pOnMinimalizeFunctor;
		boost::function<bool ()> m_pOnRestoreFunctor;
		bool m_bVisible;
		bool m_bMinimalized;

	protected:
		CSystemWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton);

		virtual ~CSystemWindow();

		virtual void ProcessEvents() = 0;

		bool OnClose();
		bool OnMinimalize();
		bool OnRestore();

	public:
		virtual const SSystemSpecificWindowData *GetSystemSpecificData() const = 0;
		virtual void Show();
		virtual void Hide();

		void SetVisible(bool bVisible);
		bool GetVisible() const;
		bool IsMinimalized() const;

		template <class CClass> void SetOnCloseFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnCloseFunctor = boost::bind(pFunctor, cClass);
		}

		template <class CClass> void SetOnMinimalizeFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnMinimalizeFunctor = boost::bind(pFunctor, cClass);
		}

		template <class CClass> void SetOnRestoreFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnRestoreFunctor = boost::bind(pFunctor, cClass);
		}
};

}

#endif /* ENGINE_SYSTEM_WINDOW_HPP */

/* EOF */

