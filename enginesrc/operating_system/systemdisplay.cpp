#include "systemdisplay.hpp"
#include "systemresolution.hpp"
#include "../useful.hpp"
#include <algorithm>

namespace engine
{

CSystemDisplay::CSystemDisplay()
{

}

CSystemDisplay::~CSystemDisplay()
{
}

void CSystemDisplay::AddResolution(CSystemResolution *pResolution)
{
	bool bMayAdd = true;
	if (m_pFilterFunctor)
		bMayAdd = m_pFilterFunctor(*pResolution);
	if (bMayAdd)
	{
		m_cResolutions.push_back(pResolution);
		std::sort(m_cResolutions.begin(), m_cResolutions.end(), CSystemResolution::LessThanPointer);
		m_cResolutions.erase(std::unique(m_cResolutions.begin(), m_cResolutions.end(), CSystemResolution::EqualToPointer), m_cResolutions.end());
	}
}

void CSystemDisplay::SetDefaultResolutionNumber(unsigned int iResolutionNumber)
{
	m_iDefaultResolutionNumber = iResolutionNumber;
}

void CSystemDisplay::SetCurrentResolutionNumber(unsigned int iResolutionNumber)
{
	m_iCurrentResolutionNumber = iResolutionNumber;
}

unsigned int CSystemDisplay::ResolutionToIndex(const CSystemResolution &cResolution)
{
	for (unsigned int i = 0; i < m_cResolutions.size(); ++i)
	{
		if (CSystemResolution::EqualToPointer(m_cResolutions[i], &cResolution))
			return i;
	}
	Error("");
	return 0;
}

const CSystemResolution &CSystemDisplay::GetCurrentResolution()
{
	return *m_cResolutions[m_iCurrentResolutionNumber];
}

const CSystemResolution &CSystemDisplay::GetDefaultResolution()
{
	return *m_cResolutions[m_iDefaultResolutionNumber];
}

unsigned int CSystemDisplay::GetResolutionsCount() const
{
	return m_cResolutions.size();
}

const CSystemResolution &CSystemDisplay::GetResolution(unsigned int iResolutionNumber) const
{
	return *m_cResolutions[iResolutionNumber];
}

bool CSystemDisplay::IsValid() const
{
	return (m_cResolutions.size() != 0);
}

}

/* EOF */
