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

bool CSystemResolution::operator < (const CSystemResolution &cResolution) const
{
	int iAreaLeft = m_iWidth * m_iHeight;
	int iAreaRight = cResolution.m_iWidth * cResolution.m_iHeight;
	if (iAreaLeft < iAreaRight)
		return true;
	else if (iAreaLeft == iAreaRight)
	{
		if (m_iBPP < cResolution.m_iBPP)
			return true;
		else if (m_iBPP == cResolution.m_iBPP)
			return m_iRefreshRate < cResolution.m_iRefreshRate;
	}
	return false;
}

bool CSystemResolution::operator == (const CSystemResolution &cResolution) const
{
	int iAreaLeft = m_iWidth * m_iHeight;
	int iAreaRight = cResolution.m_iWidth * cResolution.m_iHeight;
	return (iAreaLeft == iAreaRight && m_iBPP == cResolution.m_iBPP && m_iRefreshRate == cResolution.m_iRefreshRate);
}

bool CSystemResolution::LessThanPointer(const CSystemResolution *pLeft, const CSystemResolution *pRight)
{
	return *pLeft < *pRight;
}

bool CSystemResolution::EqualToPointer(const CSystemResolution *pLeft, const CSystemResolution *pRight)
{
	return *pLeft == *pRight;
}

}

/* EOF */
