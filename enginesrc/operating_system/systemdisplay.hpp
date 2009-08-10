#ifndef ENGINE_SYSTEM_DISPLAY_HPP
#define ENGINE_SYSTEM_DISPLAY_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <vector>

namespace engine
{

class CSystemResolution;
class CSystemWindow;

class DLLEXPORTIMPORT CSystemDisplay
{
	friend class CSystemDisplayManager;

	private:
		unsigned int m_iCurrentResolutionIndex;
		unsigned int m_iDefaultResolutionIndex;
		unsigned int m_iNextWindowId;
		std::vector<CSystemResolution *> m_cResolutions;
		std::vector<CSystemWindow *> m_cWindows;

		unsigned int GetNextWindowId();

	protected:
		CSystemDisplay();
		virtual ~CSystemDisplay();
		virtual void SetResolutionInternal(const CSystemResolution &cResolution) = 0;
		virtual CSystemWindow *AddWindowInternal(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton) = 0;
		virtual void RemoveWindowInternal(CSystemWindow *pWindow) = 0;
		void ProcessEvents();
		void AddResolution(CSystemResolution *pResolution);
		void SetCurrentResolutionIndex(unsigned int iResolutionIndex);
		void SetDefaultResolutionIndex(unsigned int iResolutionIndex);
		unsigned int ResolutionToIndex(const CSystemResolution &cResolution);

	public:
		void RestoreDefaultResolution();
		void SetResolution(unsigned int iResolutionIndex);
		void SetResolution(const CSystemResolution &cResolution);
		const CSystemResolution *GetResolution(unsigned int iResolutionIndex) const;
		const CSystemResolution *GetCurrentResolution() const;
		const CSystemResolution *GetDefaultResolution() const;
		unsigned int GetCurrentResolutionIndex() const;
		unsigned int GetDefaultResolutionIndex() const;
		unsigned int GetResolutionsCount() const;

		unsigned int AddWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption);
		unsigned int AddWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar);
		unsigned int AddWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton);
		void RemoveWindow(unsigned int iWindowId);
		CSystemWindow *GetWindow(unsigned int iWindowId);
};

}

#endif /* ENGINE_SYSTEM_DISPLAY_HPP */

/* EOF */
