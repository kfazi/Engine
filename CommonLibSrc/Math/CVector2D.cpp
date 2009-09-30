#include "../Internal.hpp"
#include "CVector2D.hpp"
#include <limits>

namespace Common
{

const CVector2D CVector2D::ZERO(0.0, 0.0);

const CVector2D CVector2D::ONE(1.0, 1.0);

CVector2D::CVector2D()
{
	*this = ZERO;
}

CVector2D::CVector2D(const double fX, const double fY)
{
	X = fX;
	Y = fY;
}

CVector2D::CVector2D(const CVector2D &cVector)
{
	X = cVector.X;
	Y = cVector.Y;
}

void CVector2D::Normalize()
{
	double fLength = GetLength();
	if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
		return;
	X /= fLength;
	Y /= fLength;
}

double CVector2D::GetLength() const
{
	return std::sqrt(X * X + Y * Y);
}

bool CVector2D::operator == (const CVector2D &cVector) const
{
	return (X == cVector.X) && (Y == cVector.Y);
}

bool CVector2D::operator != (const CVector2D &cVector) const
{
	return !(*this == cVector);
}

CVector2D &CVector2D::operator = (const CVector2D &cVector)
{
	X = cVector.X;
	Y = cVector.Y;
	return *this;
}

CVector2D &CVector2D::operator - ()
{
	X = -X;
	Y = -Y;
	return *this;
}

CVector2D &CVector2D::operator += (const CVector2D &cVector)
{
	X += cVector.X;
	Y += cVector.Y;
	return *this;
}

CVector2D &CVector2D::operator -= (const CVector2D &cVector)
{
	X -= cVector.X;
	Y -= cVector.Y;
	return *this;
}

CVector2D &CVector2D::operator *= (const CVector2D &cVector)
{
	X *= cVector.X;
	Y *= cVector.Y;
	return *this;
}

CVector2D::operator bool ()
{
	return X != 0.0 || Y != 0.0;
}

const CVector2D operator + (const CVector2D &cVector1, const CVector2D &cVector2)
{
	return CVector2D(cVector1) += cVector2;
}

const CVector2D operator - (const CVector2D &cVector1, const CVector2D &cVector2)
{
	return CVector2D(cVector1) -= cVector2;
}

const CVector2D operator * (const CVector2D &cVector1, const CVector2D &cVector2)
{
	return CVector2D(cVector1) *= cVector2;
}

}

/* EOF */

