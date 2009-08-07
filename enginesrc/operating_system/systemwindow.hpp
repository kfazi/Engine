#ifndef ENGINE_SYSTEM_WINDOW_HPP
#define ENGINE_SYSTEM_WINDOW_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

class DLLEXPORTIMPORT CSystemWindow
{
	friend class CCore;

	private:
		boost::function<bool ()> m_pOnCloseFunctor;
		boost::function<bool ()> m_pOnMinimalizeFunctor;
		boost::function<bool ()> m_pOnMaximalizeFunctor;
		bool m_bVisible;

	protected:
		CSystemWindow(const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton);

		virtual ~CSystemWindow();

		virtual void ProcessEvents() = 0;

		bool OnClose();
		bool OnMinimalize();
		bool OnMaximalize();

	public:
		virtual void Show();
		virtual void Hide();

		void SetVisible(bool bVisible);
		bool GetVisible() const;

		template <class CClass> void SetOnCloseFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnCloseFunctor = boost::bind(pFunctor, cClass);
		}

		template <class CClass> void SetOnMinimalizeFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnMinimalizeFunctor = boost::bind(pFunctor, cClass);
		}

		template <class CClass> void SetOnMaximalizeFunction(CClass *cClass, bool (CClass::*pFunctor)())
		{
			m_pOnMaximalizeFunctor = boost::bind(pFunctor, cClass);
		}
};

}

#endif /* ENGINE_SYSTEM_WINDOW_HPP */

/* EOF */

