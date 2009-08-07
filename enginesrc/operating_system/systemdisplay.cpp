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

void CSystemDisplay::RestoreDefaultResolution()
{
	SetResolution(m_iDefaultResolutionIndex);
}

void CSystemDisplay::AddResolution(CSystemResolution *pResolution)
{
	m_cResolutions.push_back(pResolution);
	/* Sort from the smallest to the biggest. */
	std::sort(m_cResolutions.begin(), m_cResolutions.end(), CSystemResolution::LessThanPointer);
	/* Remove duplicates. */
	m_cResolutions.erase(std::unique(m_cResolutions.begin(), m_cResolutions.end(), CSystemResolution::EqualToPointer), m_cResolutions.end());
}

void CSystemDisplay::SetCurrentResolutionIndex(unsigned int iResolutionIndex)
{
	m_iCurrentResolutionIndex = iResolutionIndex;
}

void CSystemDisplay::SetDefaultResolutionIndex(unsigned int iResolutionIndex)
{
	m_iDefaultResolutionIndex = iResolutionIndex;
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

const CSystemResolution *CSystemDisplay::GetCurrentResolution() const
{
	return m_cResolutions[m_iCurrentResolutionIndex];
}

const CSystemResolution *CSystemDisplay::GetDefaultResolution() const
{
	return m_cResolutions[m_iDefaultResolutionIndex];
}

unsigned int CSystemDisplay::GetCurrentResolutionIndex() const
{
	return m_iCurrentResolutionIndex;
}

void CSystemDisplay::SetResolution(unsigned int iResolutionIndex)
{
	SetCurrentResolutionIndex(iResolutionIndex);
	SetResolutionInternal(*m_cResolutions[iResolutionIndex]);
}

void CSystemDisplay::SetResolution(const CSystemResolution &cResolution)
{
	int iResolutionIndex = ResolutionToIndex(cResolution);
	SetResolution(iResolutionIndex);
}

unsigned int CSystemDisplay::GetResolutionsCount() const
{
	return m_cResolutions.size();
}

const CSystemResolution *CSystemDisplay::GetResolution(unsigned int iResolutionNumber) const
{
	return m_cResolutions[iResolutionNumber];
}

}

/* EOF */
