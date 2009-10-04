#include "CStringConvert.hpp"
#include <cstdio>

namespace Common
{

CStringConvert::CStringConvert()
{
	ResetFlags();
}

CStringConvert::~CStringConvert()
{
}

void CStringConvert::ResetFlags()
{
	SetBase(DECIMAL);
	SetNotation(NONE);
	SetBoolAlpha(false);
	SetSkipWhitespace(true);
	SetAddBase(true);
	SetBaseUpperCase(false);
	SetNumberUpperCase(false);
	SetShowDecimalPoint(false);
	SetShowPositiveSign(false);
}

void CStringConvert::SetBase(CStringConvert::EBase eBase)
{
	m_eBase = eBase;
}

CStringConvert::EBase CStringConvert::GetBase() const
{
	return m_eBase;
}

void CStringConvert::SetNotation(CStringConvert::ENotation eNotation)
{
	m_eNotation = eNotation;
}

CStringConvert::ENotation CStringConvert::GetNotation() const
{
	return m_eNotation;
}

void CStringConvert::SetBoolAlpha(bool bBoolAlpha)
{
	m_bBoolAlpha = bBoolAlpha;
}

bool CStringConvert::GetBoolAlpha() const
{
	return m_bBoolAlpha;
}

void CStringConvert::SetSkipWhitespace(bool bSkipWhitespace)
{
	m_bSkipWhitespace = bSkipWhitespace;
}

bool CStringConvert::GetSkipWhitespace() const
{
	return m_bSkipWhitespace;
}

void CStringConvert::SetAddBase(bool bAddBase)
{
	m_bAddBase = bAddBase;
}

bool CStringConvert::GetAddBase() const
{
	return m_bAddBase;
}

void CStringConvert::SetBaseUpperCase(bool bUpperCase)
{
	m_bBaseUpperCase = bUpperCase;
}

bool CStringConvert::GetBaseUpperCase() const
{
	return m_bBaseUpperCase;
}

void CStringConvert::SetNumberUpperCase(bool bUpperCase)
{
	m_bNumberUpperCase = bUpperCase;
}

bool CStringConvert::GetNumberUpperCase() const
{
	return m_bNumberUpperCase;
}

void CStringConvert::SetShowDecimalPoint(bool bShowDecimalPoint)
{
	m_bShowDecimalPoint = bShowDecimalPoint;
}

bool CStringConvert::GetShowDecimalPoint() const
{
	return m_bShowDecimalPoint;
}

void CStringConvert::SetShowPositiveSign(bool bShowPositiveSign)
{
	m_bShowPositiveSign = bShowPositiveSign;
}

bool CStringConvert::GetShowPositiveSign() const
{
	return m_bShowPositiveSign;
}

CString CStringConvert::ToString(bool bValue) const
{
	if (m_bBoolAlpha)
	{
		CString cResult;
		cResult = (bValue) ? "true" : "false";
		if (m_bNumberUpperCase)
			cResult.ToUpper();
		return cResult;
	}
	else
		return (bValue) ? "1" : "0";
}

CString CStringConvert::ToString(short iValue) const
{
	/* short has values in <-32768, 32767>, so it makes it 6 characters long in maximum */
	char aBuffer[7];
	::_snprintf(aBuffer, 7, "%d", iValue);
	aBuffer[6] = 0;
	return aBuffer;
}
/*
CString CStringConvert::ToString(unsigned short iValue) const;
CString CStringConvert::ToString(int iValue) const;
CString CStringConvert::ToString(unsigned int iValue) const;
CString CStringConvert::ToString(long iValue) const;
CString CStringConvert::ToString(unsigned long iValue) const;
CString CStringConvert::ToString(float fValue) const;
CString CStringConvert::ToString(double fValue) const;
CString CStringConvert::ToString(long double fValue) const;
CString CStringConvert::ToString(const void *pValue) const;
*/
}

/* EOF */
