#ifndef ENGINE_SYSTEM_DISPLAY_HPP
#define ENGINE_SYSTEM_DISPLAY_HPP

#include "../common.hpp"
#include <vector>

namespace engine
{

class CSystemResolution;

class DLLEXPORTIMPORT CSystemDisplay
{
	private:
		unsigned int m_iCurrentResolutionIndex;
		unsigned int m_iDefaultResolutionIndex;
		std::vector<CSystemResolution *> m_cResolutions;

	protected:
		virtual void SetResolutionInternal(const CSystemResolution &cResolution) = 0;
		void AddResolution(CSystemResolution *pResolution);
		void SetCurrentResolutionIndex(unsigned int iResolutionIndex);
		void SetDefaultResolutionIndex(unsigned int iResolutionIndex);
		unsigned int ResolutionToIndex(const CSystemResolution &cResolution);

	public:
		CSystemDisplay();
		virtual ~CSystemDisplay();
		void RestoreDefaultResolution();
		void SetResolution(unsigned int iResolutionIndex);
		void SetResolution(const CSystemResolution &cResolution);
		const CSystemResolution *GetResolution(unsigned int iResolutionIndex) const;
		const CSystemResolution *GetCurrentResolution() const;
		const CSystemResolution *GetDefaultResolution() const;
		unsigned int GetCurrentResolutionIndex() const;
		unsigned int GetDefaultResolutionIndex() const;
		unsigned int GetResolutionsCount() const;
};

}

#endif /* ENGINE_SYSTEM_DISPLAY_HPP */

/* EOF */
