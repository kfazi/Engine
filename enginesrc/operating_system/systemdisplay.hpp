#ifndef ENGINE_SYSTEM_DISPLAY_HPP
#define ENGINE_SYSTEM_DISPLAY_HPP

#include "../common.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace engine
{

class CSystemResolution;

class DLLEXPORTIMPORT CSystemDisplay
{
	private:
		unsigned int m_iCurrentResolutionNumber;
		unsigned int m_iDefaultResolutionNumber;
		std::vector<CSystemResolution *> m_cResolutions;
		boost::function<bool (const CSystemResolution &)> m_pFilterFunctor;

	protected:
		void AddResolution(CSystemResolution *pResolution);
		void SetDefaultResolutionNumber(unsigned int iResolutionNumber);
		void SetCurrentResolutionNumber(unsigned int iResolutionNumber);
		unsigned int ResolutionToIndex(const CSystemResolution &cResolution);

	public:
		CSystemDisplay();
		virtual ~CSystemDisplay();
		virtual void RefreshResolutionsList() = 0;
		virtual void SetResolution(const CSystemResolution &cResolution) = 0;
		unsigned int GetResolutionsCount() const;
		const CSystemResolution &GetResolution(unsigned int iResolutionNumber) const;
		const CSystemResolution &GetCurrentResolution();
		const CSystemResolution &GetDefaultResolution();
		bool IsValid() const;

		template <class CClass> void SetResolutionsListFilter(CClass *cClass, bool (CClass::*pFilterFunctor)(const CSystemResolution &))
		{
			m_pFilterFunctor = boost::bind(pFilterFunctor, cClass);
			RefreshResolutionsList();
		}
};

}

#endif /* ENGINE_SYSTEM_DISPLAY_HPP */

/* EOF */
