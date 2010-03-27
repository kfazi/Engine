#include "StreamBase.hpp"

namespace Common
{

StreamBase::StreamBase()
{
	ResetFlags();
}

void StreamBase::ResetFlags()
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

void StreamBase::SetBase(StreamBase::Base base)
{
	mBase = base;
}

StreamBase::Base StreamBase::GetBase() const
{
	return mBase;
}

void StreamBase::SetNotation(StreamBase::Notation notation)
{
	mNotation = notation;
}

StreamBase::Notation StreamBase::GetNotation() const
{
	return mNotation;
}

void StreamBase::SetBoolAlpha(bool boolAlpha)
{
	mBoolAlpha = boolAlpha;
}

bool StreamBase::GetBoolAlpha() const
{
	return mBoolAlpha;
}

void StreamBase::SetSkipWhitespace(bool skipWhitespace)
{
	mSkipWhitespace = skipWhitespace;
}

bool StreamBase::GetSkipWhitespace() const
{
	return mSkipWhitespace;
}

void StreamBase::SetAddBase(bool addBase)
{
	mAddBase = addBase;
}

bool StreamBase::GetAddBase() const
{
	return mAddBase;
}

void StreamBase::SetBaseUpperCase(bool upperCase)
{
	mBaseUpperCase = upperCase;
}

bool StreamBase::GetBaseUpperCase() const
{
	return mBaseUpperCase;
}

void StreamBase::SetNumberUpperCase(bool upperCase)
{
	mNumberUpperCase = upperCase;
}

bool StreamBase::GetNumberUpperCase() const
{
	return mNumberUpperCase;
}

void StreamBase::SetShowDecimalPoint(bool showDecimalPoint)
{
	mShowDecimalPoint = showDecimalPoint;
}

bool StreamBase::GetShowDecimalPoint() const
{
	return mShowDecimalPoint;
}

void StreamBase::SetShowPositiveSign(bool showPositiveSign)
{
	mShowPositiveSign = showPositiveSign;
}

bool StreamBase::GetShowPositiveSign() const
{
	return mShowPositiveSign;
}

}

/* EOF */
