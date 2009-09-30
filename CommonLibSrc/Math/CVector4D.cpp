#include "../Internal.hpp"
#include "CVector4D.hpp"
#include <limits>

namespace Common
{

const CVector4D CVector4D::ZERO(0.0, 0.0, 0.0, 0.0);

const CVector4D CVector4D::ONE(1.0, 1.0, 1.0, 1.0);

CVector4D::CVector4D()
{
	*this = ZERO;
}

CVector4D::CVector4D(const double fX, const double fY, const double fZ, const double fW)
{
	X = fX;
	Y = fY;
	Z = fZ;
	W = fW;
}

CVector4D::CVector4D(const CVector4D &cVector)
{
	X = cVector.X;
	Y = cVector.Y;
	Z = cVector.Z;
	W = cVector.W;
}

void CVector4D::Normalize()
{
	double fLength = GetLength();
	if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
		return;
	X = X / fLength;
	Y = Y / fLength;
	Z = Z / fLength;
	W = W / fLength;
}

double CVector4D::GetLength() const
{
	return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

bool CVector4D::operator == (const CVector4D &cVector) const
{
	return (X == cVector.X) && (Y == cVector.Y) && (Z == cVector.Z) && (W == cVector.W);
}

bool CVector4D::operator != (const CVector4D &cVector) const
{
	return !(*this == cVector);
}

CVector4D &CVector4D::operator = (const CVector4D &cVector)
{
	X = cVector.X;
	Y = cVector.Y;
	Z = cVector.Z;
	W = cVector.W;
	return *this;
}

CVector4D CVector4D::operator - ()
{
	return CVector4D(-X, -Y, -Z, -W);
}

CVector4D &CVector4D::operator += (const CVector4D &cVector)
{
	X += cVector.X;
	Y += cVector.Y;
	Z += cVector.Z;
	W += cVector.W;
	return *this;
}

CVector4D &CVector4D::operator -= (const CVector4D &cVector)
{
	X -= cVector.X;
	Y -= cVector.Y;
	Z -= cVector.Z;
	W -= cVector.W;
	return *this;
}

CVector4D &CVector4D::operator *= (const CVector4D &cVector)
{
	X *= cVector.X;
	Y *= cVector.Y;
	Z *= cVector.Z;
	W *= cVector.W;
	return *this;
}

CVector4D::operator bool ()
{
	return X != 0.0 || Y != 0.0 || Z != 0.0 || W != 0.0;
}

const CVector4D operator + (const CVector4D &cVector1, const CVector4D &cVector2)
{
	return CVector4D(cVector1) += cVector2;
}

const CVector4D operator - (const CVector4D &cVector1, const CVector4D &cVector2)
{
	return CVector4D(cVector1) -= cVector2;
}

const CVector4D operator * (const CVector4D &cVector1, const CVector4D &cVector2)
{
	return CVector4D(cVector1) *= cVector2;
}

}

/* EOF */
