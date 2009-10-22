#include "CStreamBase.hpp"

namespace Common
{

CStreamBase::CStreamBase()
{
	ResetFlags();
}

void CStreamBase::ResetFlags()
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

void CStreamBase::SetBase(CStreamBase::EBase eBase)
{
	m_eBase = eBase;
}

CStreamBase::EBase CStreamBase::GetBase() const
{
	return m_eBase;
}

void CStreamBase::SetNotation(CStreamBase::ENotation eNotation)
{
	m_eNotation = eNotation;
}

CStreamBase::ENotation CStreamBase::GetNotation() const
{
	return m_eNotation;
}

void CStreamBase::SetBoolAlpha(bool bBoolAlpha)
{
	m_bBoolAlpha = bBoolAlpha;
}

bool CStreamBase::GetBoolAlpha() const
{
	return m_bBoolAlpha;
}

void CStreamBase::SetSkipWhitespace(bool bSkipWhitespace)
{
	m_bSkipWhitespace = bSkipWhitespace;
}

bool CStreamBase::GetSkipWhitespace() const
{
	return m_bSkipWhitespace;
}

void CStreamBase::SetAddBase(bool bAddBase)
{
	m_bAddBase = bAddBase;
}

bool CStreamBase::GetAddBase() const
{
	return m_bAddBase;
}

void CStreamBase::SetBaseUpperCase(bool bUpperCase)
{
	m_bBaseUpperCase = bUpperCase;
}

bool CStreamBase::GetBaseUpperCase() const
{
	return m_bBaseUpperCase;
}

void CStreamBase::SetNumberUpperCase(bool bUpperCase)
{
	m_bNumberUpperCase = bUpperCase;
}

bool CStreamBase::GetNumberUpperCase() const
{
	return m_bNumberUpperCase;
}

void CStreamBase::SetShowDecimalPoint(bool bShowDecimalPoint)
{
	m_bShowDecimalPoint = bShowDecimalPoint;
}

bool CStreamBase::GetShowDecimalPoint() const
{
	return m_bShowDecimalPoint;
}

void CStreamBase::SetShowPositiveSign(bool bShowPositiveSign)
{
	m_bShowPositiveSign = bShowPositiveSign;
}

bool CStreamBase::GetShowPositiveSign() const
{
	return m_bShowPositiveSign;
}

}

/* EOF */
