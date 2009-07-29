#include "systemresolution.hpp"

namespace engine
{

CSystemResolution::CSystemResolution(unsigned int iWidth, unsigned int iHeight, unsigned int iBPP, unsigned int iRefreshRate)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iBPP = iBPP;
	m_iRefreshRate = iRefreshRate;
}

unsigned int CSystemResolution::GetWidth() const
{
	return m_iWidth;
}

unsigned int CSystemResolution::GetHeight() const
{
	return m_iHeight;
}

unsigned int CSystemResolution::GetBPP() const
{
	return m_iBPP;
}

unsigned int CSystemResolution::GetRefreshRate() const
{
	return m_iRefreshRate;
}

bool CSystemResolution::LessThanPointer(const CSystemResolution *pLeft, const CSystemResolution *pRight)
{
	int iAreaLeft = pLeft->m_iWidth * pLeft->m_iHeight;
	int iAreaRight = pRight->m_iWidth * pRight->m_iHeight;
	if (iAreaLeft < iAreaRight)
		return true;
	else if (iAreaLeft == iAreaRight)
	{
		if (pLeft->m_iBPP < pRight->m_iBPP)
			return true;
		else if (pLeft->m_iBPP == pRight->m_iBPP)
			return pLeft->m_iRefreshRate < pRight->m_iRefreshRate;
	}
	return false;
}

bool CSystemResolution::EqualToPointer(const CSystemResolution *pLeft, const CSystemResolution *pRight)
{
	int iAreaLeft = pLeft->m_iWidth * pLeft->m_iHeight;
	int iAreaRight = pRight->m_iWidth * pRight->m_iHeight;
	return (iAreaLeft == iAreaRight && pLeft->m_iBPP == pRight->m_iBPP && pLeft->m_iRefreshRate == pRight->m_iRefreshRate);
}

}

/* EOF */
